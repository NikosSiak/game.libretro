/*
 *      Copyright (C) 2014-2016 Team Kodi
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this Program; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include "LibretroResources.h"
#include "audio/AudioStream.h"
#include "memory/MemoryMap.h"
#include "settings/LibretroSettings.h"
#include "video/VideoStream.h"

#include "kodi_game_types.h"

#include <memory>
#include <string>

namespace ADDON { class CHelper_libXBMC_addon; }
class CHelper_libKODI_game;

namespace LIBRETRO
{
  class CClientBridge;
  class CLibretroDLL;

  class CLibretroEnvironment
  {
  public:
    static CLibretroEnvironment& Get(void);

    void Initialize(ADDON::CHelper_libXBMC_addon* xbmc,
                    CHelper_libKODI_game*         frontend,
                    CLibretroDLL*                 client,
                    CClientBridge*                clientBridge,
                    const AddonProps_Game*        gameClientProps);

    void Deinitialize(void);

    ADDON::CHelper_libXBMC_addon* GetXBMC(void)         { return m_xbmc; }
    CHelper_libKODI_game*         GetFrontend(void)     { return m_frontend; }
    CLibretroDLL*                 GetClient(void)       { return m_client; }
    CClientBridge*                GetClientBridge(void) { return m_clientBridge; }

    CVideoStream& Video(void) { return m_videoStream; }
    CAudioStream& Audio(void) { return m_audioStream; }

    void CloseStreams();

    void UpdateVideoGeometry(const retro_game_geometry &geometry);

    /*!
     * Returns the pixel format set by the libretro core. Instead of forwarding
     * this to the frontend, we store the value and report it on calls to
     * VideoRefresh().
     */
    GAME_PIXEL_FORMAT GetVideoFormat(void) const { return m_videoFormat; }

    GAME_VIDEO_ROTATION GetVideoRotation() const { return m_videoRotation; }

    /*!
     * Invoked when the frontend transfers a setting to the add-on.
     */
    void SetSetting(const std::string& name, const std::string& value);

    std::string GetResourcePath(const char* relPath);

    /*!
     * \brief Called after game has been run for a frame
     */
    void OnFrameEnd();

    bool EnvironmentCallback(unsigned cmd, void* data);

  private:
    CLibretroEnvironment(void);

    ADDON::CHelper_libXBMC_addon* m_xbmc;
    CHelper_libKODI_game*         m_frontend;
    CLibretroDLL*                 m_client;
    CClientBridge*                m_clientBridge;
    CVideoStream                  m_videoStream;
    CAudioStream                  m_audioStream;

    GAME_PIXEL_FORMAT   m_videoFormat;
    GAME_VIDEO_ROTATION m_videoRotation;

    CLibretroSettings m_settings;
    CLibretroResources m_resources;

    CMemoryMap m_mmaps;
  };
} // namespace LIBRETRO
