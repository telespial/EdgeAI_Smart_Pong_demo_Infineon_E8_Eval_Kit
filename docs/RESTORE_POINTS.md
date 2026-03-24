# Restore Points (Golden / Failsafe)

This repo uses two tags to mark known recoverable firmware states:

- `golden-e8-smart-pong`
- `failsafe-e8-smart-pong`

Both tags are intended to point to a verified build+flash commit.

## Current Tagged Baseline Intent

Current baseline includes:
- Smart Pong runtime selected by build flags (`APP_INSULIN_PUMP_MODE=0`, `APP_SMART_PONG_MODE=1`)
- Two-line `SMART` / `PONG` startup title
- `EDGEAI_FIXED_FPS=180`
- Higher gameplay pace with max ball speed cap tuned to `+50%` over prior baseline
- Mixed-mode AI balancing update (reduced fixed EdgeAI pre-bias while preserving adaptive learning)
- Win counter integrity fix:
  - Bottom `WINS` totals update only on true match completion
  - Non-match `game_reset()` paths no longer inflate wins
- Verified build/program on `KIT_PSE84_EVAL_EPC2` with `CONFIG_DISPLAY=W4P3INCH_DISP`

Most recent verification:
- Date: `2026-03-24`
- Device: `PSE846GPS2DBZC4A` (Rev `B0`)
- Program artifact: `firmware_kit_epc2/build/app_combined.hex`
- Restore artifacts:
  - `failsafe/e8_smart_pong_20260324_095648_top_role_labels_app_combined.hex`
  - `failsafe/e8_smart_pong_20260324_095648_top_role_labels_proj_cm55.elf`

## Restore to Golden/Failsafe

```bash
git fetch --tags
git checkout golden-e8-smart-pong
```

or

```bash
git checkout failsafe-e8-smart-pong
```

Then build/flash using `docs/BUILD_FLASH_E8.md`.

## Tag Update Policy

Only move these tags after:
1. Successful build
2. Successful flash
3. Basic on-device verification (boot/display/input)
