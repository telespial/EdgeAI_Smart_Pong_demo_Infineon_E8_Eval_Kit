# EdgeAI Smart Pong Demo for Infineon PSOC Edge E8 Eval Kit

This repository is the working integration and firmware workspace for **Smart Pong** on the **Infineon PSOC Edge E8 Evaluation Kit** with the **4.3" display**.

It includes:
- The active E8 firmware project used for build/flash
- Imported upstream Infineon LVGL demo source for reference
- Original NXP Smart Pong source for porting reference
- Board docs and local bring-up notes

## Current Golden Runtime Defaults

Boot defaults are currently:
- **Mode:** `P0`
- **Difficulty:** `D2`
- **Skill mode:** `ALGO/AI` (left ALGO, right EDGEAI)

## Repository Layout

- `firmware_kit_epc2/` - Primary active firmware project (build/flash target)
- `Infineon_e8_eval_sourcecode/` - Upstream Infineon example source snapshot
- `EdgeAI_smart_pong_demo_NXP_FRDM-MCXN947/` - Original NXP Smart Pong reference
- `infineon_e8_eval_docs/` - Board docs, schematics, datasheets, bring-up references
- `docs/` - Project-specific build, calibration, and restore documentation

## Build and Flash (Primary)

Build and flash from:

`/home/user/projects/embedded/codemaster/projects/Infineon/PSOC_EDGE_E8_EVAL/firmware_kit_epc2`

See full instructions in:
- `docs/BUILD_FLASH_E8.md`

## Accelerometer + Controls

Latest mapping and orientation notes:
- `docs/ACCEL_AND_CONTROLS.md`

## Restore Points

Golden and failsafe restore process and tags:
- `docs/RESTORE_POINTS.md`

## Notes

- This project is actively tuned on real hardware.
- If panel/controls behavior changes after updates, use the restore point tags documented in `docs/RESTORE_POINTS.md`.
