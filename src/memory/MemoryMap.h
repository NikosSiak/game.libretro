/*
 *      Copyright (C) 2020 Team Kodi
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

#include "libretro/libretro.h"

#include <vector>

namespace LIBRETRO
{
struct MemoryDescriptor
{
  retro_memory_descriptor descriptor;
  size_t disconnectMask;
};

class CMemoryMap
{
public:
  size_t GetNumOfDescriptors();
  void AddDescriptor(const retro_memory_descriptor& descriptor);
  bool PreprocessDescriptors();

private:
  size_t AddBitsDown(size_t num);
  size_t Inflate(size_t addr, size_t mask);
  size_t Reduce(size_t addr, size_t mask);
  size_t HighestBit(size_t num);

  std::vector<MemoryDescriptor> m_memoryDescriptors;
};
}
