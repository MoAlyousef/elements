/*=============================================================================
   Copyright (c) 2016-2020 Joel de Guzman

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#include <infra/support.hpp>
#include <elements/support/rect.hpp>
#include <algorithm>

namespace cycfi { namespace elements
{
   bool intersects(rect const& a, rect const& b)
   {
      if (!is_valid(a) || !is_valid(b))
         return false;

      return
         (std::max(b.left, b.left) <= std::min(b.right, b.right)) &&
         (std::max(b.top, b.top) <= std::min(b.bottom, b.bottom))
         ;
   }

   rect max(rect const& a, rect const& b)
   {
      return {
         std::min(a.left, b.left),
         std::min(a.top, b.top),
         std::max(a.right, b.right),
         std::max(a.bottom, b.bottom)
      };
   }

   rect min(rect const& a, rect const& b)
   {
      return {
         std::max(a.left, b.left),
         std::max(a.top, b.top),
         std::min(a.right, b.right),
         std::min(a.bottom, b.bottom)
      };
   }

   rect center(rect const& r_, rect const& encl)
   {
      rect r = r_;
      double dx = (encl.width() - r.width()) / 2.0;
      double dy = (encl.height() - r.height()) / 2.0;
      r = r.move_to(encl.left, encl.top);
      r = r.move(dx, dy);
      return r;
   }

   rect center_h(rect const& r_, rect const& encl)
   {
      rect r = r_;
      double dx = (encl.width() - r.width()) / 2.0;
      r = r.move_to(encl.left, r.top);
      r = r.move(dx, 0.0);
      return r;
   }

   rect center_v(rect const& r_, rect const& encl)
   {
      rect r = r_;
      double dy = (encl.height() - r.height()) / 2.0;
      r = r.move_to(r.left, encl.top);
      r = r.move(0.0, dy);
      return r;
   }

   rect align(rect const& r_, rect const& encl, double x_align, double y_align)
   {
      rect r = r_;
      r = r.move_to(
         encl.left + ((encl.width() - r.width()) * x_align),
         encl.top + ((encl.height() - r.height()) * y_align)
      );
      return r;
   }

   rect align_h(rect const& r_, rect const& encl, double x_align)
   {
      rect r = r_;
      r = r.move_to(
         encl.left + ((encl.width() - r.width()) * x_align), r.top
      );
      return r;
   }

   rect align_v(rect const& r_, rect const& encl, double y_align)
   {
      rect r = r_;
      r = r.move_to(
         r.left, encl.top + ((encl.height() - r.height()) * y_align)
      );
      return r;
   }

   rect clip(rect const& r_, rect const& encl)
   {
      rect r = r_;
      clamp_min(r.left, encl.left);
      clamp_min(r.top, encl.top);
      clamp_max(r.right, encl.right);
      clamp_max(r.bottom, encl.bottom);
      return r;
   }
}}
