// Basic class for canvas layouts
//
// Copyright (C) 2014  Thomas Geymayer <tomgey@gmail.com>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301, USA

#include "Layout.hxx"
#include <simgear/debug/logstream.hxx>

namespace simgear
{
namespace canvas
{

  //----------------------------------------------------------------------------
  void Layout::update()
  {
    if( !(_flags & (LAYOUT_DIRTY | SIZE_INFO_DIRTY)) )
      return;

    doLayout(_geometry);

    _flags &= ~LAYOUT_DIRTY;
  }

  //----------------------------------------------------------------------------
  void Layout::invalidate()
  {
    LayoutItem::invalidate();
    _flags |= LAYOUT_DIRTY;
  }

  //----------------------------------------------------------------------------
  void Layout::setGeometry(const SGRecti& geom)
  {
    if( geom == _geometry )
      return;

    _geometry = geom;
    _flags |= LAYOUT_DIRTY;

    update();
  }

  //----------------------------------------------------------------------------
  void Layout::ItemData::reset()
  {
    layout_item = 0;
    size_hint   = 0;
    min_size    = 0;
    max_size    = 0;
    padding_orig= 0;
    padding     = 0;
    size        = 0;
    stretch     = 0;
    done        = false;
  }

  //----------------------------------------------------------------------------
  void Layout::safeAdd(int& a, int b)
  {
    if( SGLimits<int>::max() - b < a )
      a = SGLimits<int>::max();
    else
      a += b;
  }

  //----------------------------------------------------------------------------
  void Layout::distribute(std::vector<ItemData>& items, const ItemData& space)
  {
    const int num_children = static_cast<int>(items.size());
    _num_not_done = num_children;

    SG_LOG( SG_GUI,
            SG_DEBUG,
            "Layout::distribute(" << num_children << " items)" );

    if( space.size < space.min_size )
    {
      // TODO
      SG_LOG( SG_GUI, SG_WARN, "Layout: not enough size (not implemented)");
    }
    else if( space.size < space.max_size )
    {
      _sum_stretch = 0;
      _space_stretch = 0;

      bool less_then_hint = space.size < space.size_hint;

      // Give min_size/size_hint to all items
      _space_left = space.size
                  - (less_then_hint ? space.min_size : space.size_hint);
      for(int i = 0; i < num_children; ++i)
      {
        ItemData& d = items[i];
        d.size = less_then_hint ? d.min_size : d.size_hint;
        d.padding = d.padding_orig;
        d.done = d.size >= (less_then_hint ? d.size_hint : d.max_size);

        if( d.done )
        {
          _num_not_done -= 1;
          continue;
        }

        if( d.stretch > 0 )
        {
          _sum_stretch += d.stretch;
          _space_stretch += d.size;
        }
      }

      // Distribute remaining space to increase the size of each item up to its
      // size_hint/max_size
      while( _space_left > 0 )
      {
        if( _num_not_done <= 0 )
        {
          SG_LOG(SG_GUI, SG_WARN, "space left, but no more items?");
          break;
        }

        int space_per_element = std::max(1, _space_left / _num_not_done);

        SG_LOG(SG_GUI, SG_DEBUG, "space/element=" << space_per_element);

        for(int i = 0; i < num_children; ++i)
        {
          ItemData& d = items[i];

          SG_LOG(
            SG_GUI,
            SG_DEBUG,
            i << ") left=" << _space_left
              << ", not_done=" << _num_not_done
              << ", sum=" << _sum_stretch
              << ", stretch=" << _space_stretch
              << ", stretch/unit=" << _space_stretch / std::max(1, _sum_stretch)
          );

          if( d.done )
            continue;

          if( _sum_stretch > 0 && d.stretch <= 0 )
            d.done = true;
          else
          {
            int target_size = 0;
            int max_size = less_then_hint ? d.size_hint : d.max_size;

            if( _sum_stretch > 0 )
            {
              target_size = (d.stretch * (_space_left + _space_stretch))
                          / _sum_stretch;

              // Item would be smaller than minimum size or larger than maximum
              // size, so just keep bounded size and ignore stretch factor
              if( target_size <= d.size || target_size >= max_size )
              {
                d.done = true;
                _sum_stretch -= d.stretch;
                _space_stretch -= d.size;

                if( target_size >= max_size )
                  target_size = max_size;
                else
                  target_size = d.size;
              }
              else
                _space_stretch += target_size - d.size;
            }
            else
            {
              // Give space evenly to all remaining elements in this round
              target_size = d.size + std::min(_space_left, space_per_element);

              if( target_size >= max_size )
              {
                d.done = true;
                target_size = max_size;
              }
            }

            int old_size = d.size;
            d.size = target_size;
            _space_left -= d.size - old_size;
          }

          if( d.done )
          {
            _num_not_done -= 1;

            if( _sum_stretch <= 0 && d.stretch > 0 )
              // Distribute remaining space evenly to all non-stretchable items
              // in a new round
              break;
          }
        }
      }
    }
    else
    {
      _space_left = space.size - space.max_size;
      for(int i = 0; i < num_children; ++i)
      {
        ItemData& d = items[i];
        d.size = d.max_size;

        // Add superfluous space as padding
        d.padding = d.padding_orig + _space_left
                                   // Padding after last child...
                                   / (_num_not_done + 1);

        _space_left -= d.padding - d.padding_orig;
        _num_not_done -= 1;
      }
    }

    SG_LOG(SG_GUI, SG_DEBUG, "distribute:");
    for(int i = 0; i < num_children; ++i)
    {
      ItemData const& d = items[i];
      SG_LOG( SG_GUI,
              SG_DEBUG,
              i << ") pad=" << d.padding
                << ", size = " << d.size );
    }
  }

} // namespace canvas
} // namespace simgear