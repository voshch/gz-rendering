/*
 * Copyright (C) 2026 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef GZ_RENDERING_OGRE2_OGRE2SHAREDFULLSCREENRECTS_HH_
#define GZ_RENDERING_OGRE2_OGRE2SHAREDFULLSCREENRECTS_HH_

#ifdef _MSC_VER
  #pragma warning(push, 0)
#endif
#include <Compositor/OgreCompositorManager2.h>
#include <OgreHlmsManager.h>
#include <OgreRectangle2D.h>
#include <OgreRoot.h>
#ifdef _MSC_VER
  #pragma warning(pop)
#endif

namespace gz
{
  namespace rendering
  {
    inline namespace GZ_RENDERING_VERSION_NAMESPACE {
    /// \brief Point the compositor's shared fullscreen quad and triangle
    /// at the default datablock. Every quad pass links them to its own
    /// material, so call this before removing a material a quad pass used,
    /// or the next quad pass unlinks them from a freed datablock.
    /// \param[in] _root Ogre root owning the compositor manager
    inline void ReleaseSharedFullscreenRects(Ogre::Root *_root)
    {
      Ogre::CompositorManager2 *compMgr = _root->getCompositorManager2();
      Ogre::HlmsDatablock *fallback =
          _root->getHlmsManager()->getDefaultDatablock();
      for (Ogre::v1::Rectangle2D *rect :
           {compMgr->getSharedFullscreenQuad(),
            compMgr->getSharedFullscreenTriangle()})
      {
        if (rect && rect->getDatablock() != fallback)
          rect->setDatablock(fallback);
      }
    }
    }
  }
}
#endif
