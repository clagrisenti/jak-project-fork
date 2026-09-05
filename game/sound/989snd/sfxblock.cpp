#include "sfxblock.h"

#include "blocksound_handler.h"
#include "sfxgrain.h"

#include "common/log/log.h"

#include "third-party/magic_enum.hpp"

namespace snd {

std::optional<std::unique_ptr<SoundHandler>> SFXBlock::MakeHandler(VoiceManager& vm,
                                                                   u32 sound_id,
                                                                   s32 vol,
                                                                   s32 pan,
                                                                   SndPlayParams& params,
                                                                   s32 current_tick,
                                                                   u32 owner) {
  auto& SFX = Sounds[sound_id];

  if (SFX.Grains.empty()) {
    return std::nullopt;
  }

  auto handler = std::make_unique<BlockSoundHandler>(*this, SFX, vm, vol, pan, params, sound_id,
                                                     current_tick, owner);
  return handler;
}

std::optional<u32> SFXBlock::GetSoundByName(const char* name) {
  auto sound = Names.find(name);
  if (sound != Names.end()) {
    return sound->second;
  }

  return std::nullopt;
}

void SFXBlock::DebugPrintAllSounds() {
  for (const auto& [name, id] : Names) {
    lg::info("{} : {}", name.c_str(), id);
    const auto& sound = Sounds.at(id);
    lg::info(" Vol: {}", sound.Vol);
    lg::info(" VolGroup: {}", sound.VolGroup);
    lg::info(" Pan: {}", sound.Pan);
    lg::info(" InstanceLimit: {}", sound.InstanceLimit);
    lg::info(" Flags: 0x{0:#x}", sound.Flags.flags);
    lg::info(" User: 0x{0:#x} 0x{1:#x} 0x{3:#x} 0x{3:#x}", sound.UserData.data[0],
             sound.UserData.data[1], sound.UserData.data[2], sound.UserData.data[3]);
    lg::info(" Grains\n");
    for (const auto& grain : sound.Grains) {
      lg::print(fmt::format("  {} ({})\n", magic_enum::enum_name(grain.Type), (int)grain.Type));
    }
  }
}

}  // namespace snd
