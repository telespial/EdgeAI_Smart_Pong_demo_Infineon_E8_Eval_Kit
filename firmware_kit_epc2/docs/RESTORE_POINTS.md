# RESTORE_POINTS

## Purpose
Known-good checkpoints for fast recovery when development changes break boot, display, or flashing.

## Tagged Restore Points
- `failsafe_music_custom_build_2026_03_21`
  - Meaning: Last stable LVGL music-demo baseline with the custom banner path.
  - Expected screen: Music demo + `CUSTOM BUILD` text.

- `golden_smart_pong_prep_boot_2026_03_21`
  - Meaning: Current golden baseline for Smart Pong bring-up.
  - Expected screen: `SMART PONG - PORT PREP`.

## Restore Procedure
1. Fetch tags:
   ```bash
   git fetch --tags
   ```
2. Checkout restore point:
   ```bash
   git checkout <tag>
   ```
3. Build/program using runbook environment:
   ```bash
   make clean TOOLCHAIN=GCC_ARM
   make program TOOLCHAIN=GCC_ARM
   ```

## Notes
- Use `failsafe_*` when recovering from major regressions.
- Use `golden_*` as the default base for new Pong feature work.
