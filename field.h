#pragma once
#include "structuer.h"
#include"enum.h"
#include"common.h"
#include"camera.h"
#include "player.h"
#include "rope.h"
#include "easing.h"
#include "colorname.h"


void Effect(Particle* particle, Field* field);

void ParticleInitialize(PARTICLE* particle);

void ParticleUpDate(PARTICLE* particle, CameraRelated* cr, GameObject* go, Key* key);

void ParticleDraw(PARTICLE* particle);
