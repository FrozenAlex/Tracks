#pragma once

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Transform.hpp"

#include "Track.h"

#include <utility>
#include <vector>
#include <string>
#include <optional>
#include "custom-types/shared/types.hpp"
#include "custom-types/shared/macros.hpp"

namespace Tracks {
struct GameObjectTrackControllerData {
  std::vector<Track*> const _track;

  bool const v2;

  GameObjectTrackControllerData(std::vector<Track*> track, bool v2) : _track(std::move(track)), v2(v2) {}

  UnorderedEventCallback<> PositionUpdate;
  UnorderedEventCallback<> ScaleUpdate;
  UnorderedEventCallback<> RotationUpdate;
};
} // namespace Tracks

DECLARE_CLASS_CODEGEN(Tracks, GameObjectTrackController, UnityEngine::MonoBehaviour,

                      private
                      : static int nextId;

                      // Unity doesn't like copying my data, so we store it and copy the ID.
                      static std::unordered_map<int, GameObjectTrackControllerData> _dataMap;

                      DECLARE_INSTANCE_FIELD_DEFAULT(int, id, -1);
                      DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, parent);
                      DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, origin);

                      // This is retrived from the data map since Unity doesn't copy it.
                      GameObjectTrackControllerData * data; uint64_t lastCheckedTime;

                      void UpdateData(bool force);

                      DECLARE_INSTANCE_METHOD(void, Awake); DECLARE_INSTANCE_METHOD(void, OnEnable);
                      DECLARE_INSTANCE_METHOD(void, Update); DECLARE_INSTANCE_METHOD(void, OnTransformParentChanged);
                      public
                      : GameObjectTrackControllerData & getTrackControllerData();

                      static bool LeftHanded;

                      static std::optional<GameObjectTrackController*> HandleTrackData(
                          UnityEngine::GameObject * gameObject, std::vector<Track*> const& track,
                          float noteLinesDistance, bool v2, bool overwrite = false);

                      static void ClearData();

                      DECLARE_SIMPLE_DTOR(); DECLARE_DEFAULT_CTOR();)
