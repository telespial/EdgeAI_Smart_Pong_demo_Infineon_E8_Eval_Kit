# Project Status Snapshot

## Board

- Target: Infineon PSOC Edge E8 Evaluation Kit
- Display profile: `W4P3INCH_DISP` (4.3 inch)

## Current Runtime Defaults

- Mode: `P0`
- Difficulty: `D2`
- Match: `100`
- Persistence: `OFF`
- Volume: `60`

## Active Firmware Path

- `/home/user/projects/embedded/codemaster/projects/Infineon/PSOC_EDGE_E8_EVAL/firmware_kit_epc2`

## Current Visual/Runtime Behavior

- Startup shows two-line `SMART` / `PONG` title, then enters gameplay.
- Fixed-step target increased to `180 FPS` (from `60 FPS`) for faster update cadence.
- Ball max speed cap increased by `+50%` over the prior baseline.
- Runtime app selection is pinned to Smart Pong in the build flags:
  - `APP_INSULIN_PUMP_MODE=0`
  - `APP_SMART_PONG_MODE=1`
- Bottom `WINS` counter logic fixed:
  - Match wins now increment only after a real match completion.
  - Menu/config resets no longer accidentally increment wins.

## Control Tuning

- Accel outputs:
  - `accel_ax = sensor X`
  - `accel_ay = -sensor Y`
- P0 vertical nudge:
  - `g->ball.vy -= ay * k * dt`

## AI Balance Status (2026-03-24)

- Mixed-mode EdgeAI strength reduced to avoid 99% win behavior.
- Key balancing changes:
  - Lower fixed EdgeAI lead bonus in mixed mode
  - Lower fixed trailing catch-up amplification
  - Lower fixed mixed-mode noise-reduction advantage
  - Preserve adaptive learning gains so EdgeAI still improves from play outcomes
  - Score-lead anti-runaway handicap retained

## Verification (2026-03-24)

- Build: `make build TOOLCHAIN=GCC_ARM CONFIG_DISPLAY=W4P3INCH_DISP -j8` ✅
- Flash: `make program TOOLCHAIN=GCC_ARM CONFIG_DISPLAY=W4P3INCH_DISP` ✅
- Detected board during flash: `PSE846GPS2DBZC4A` (Rev `B0`)
- UI update: enlarged top HUD role labels (`HUMAN` / `ALGO` / `EdgeAI`) and reflashed.

## Restore Policy

Use tagged restore points:
- `golden-e8-smart-pong`
- `failsafe-e8-smart-pong`
- Restore artifacts:
  - `failsafe/e8_smart_pong_20260324_095648_top_role_labels_app_combined.hex`
  - `failsafe/e8_smart_pong_20260324_095648_top_role_labels_proj_cm55.elf`
