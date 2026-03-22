# RESTORE_POINTS

## Purpose
Known-good checkpoints for fast recovery when development changes break boot, display, or flashing.

## Tagged Restore Points (Repo-Level)
- `failsafe-e8-smart-pong`
  - Meaning: Last known-stable Smart Pong restore point for rapid recovery.
- `golden-e8-smart-pong`
  - Meaning: Current development base for Smart Pong feature work.

## Expected Behavior At Current Baseline
- Boot shows centered `SMART` / `PONG` banner then enters gameplay.
- Build/flash target: `KIT_PSE84_EVAL_EPC2` with `CONFIG_DISPLAY=W4P3INCH_DISP`.
- Runtime tuning:
  - `EDGEAI_FIXED_FPS=180`
  - max ball speed cap: `+50%` over prior baseline.
  - audio event tones and win tune enabled.
  - volume UI row enabled (`VOL DN  xxx  UP`), default `VOL=60`.

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
    make program TOOLCHAIN=GCC_ARM CONFIG_DISPLAY=W4P3INCH_DISP
   ```

## Notes
- Use `failsafe-e8-smart-pong` when recovering from major regressions.
- Use `golden-e8-smart-pong` as the default base for new feature work.
