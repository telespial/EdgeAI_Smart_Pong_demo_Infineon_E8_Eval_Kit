# Project Status Snapshot

## Board

- Target: Infineon PSOC Edge E8 Evaluation Kit
- Display profile: `W4P3INCH_DISP` (4.3 inch)

## Current Runtime Defaults

- Mode: `P0`
- Difficulty: `D2`
- Skill: `ALGO/AI` (left ALGO, right EDGEAI)

## Active Firmware Path

- `/home/user/projects/embedded/codemaster/projects/Infineon/PSOC_EDGE_E8_EVAL/firmware_kit_epc2`

## Current Visual/Runtime Behavior

- Startup now skips the `SMART PONG` title card and enters gameplay directly.
- Fixed-step target increased to `180 FPS` (from `60 FPS`) for faster update cadence.
- Ball max speed cap increased by `+50%` over the prior baseline.

## Control Tuning

- Accel outputs:
  - `accel_ax = sensor X`
  - `accel_ay = -sensor Y`
- P0 vertical nudge:
  - `g->ball.vy -= ay * k * dt`

## Restore Policy

Use tagged restore points:
- `golden-e8-smart-pong`
- `failsafe-e8-smart-pong`
