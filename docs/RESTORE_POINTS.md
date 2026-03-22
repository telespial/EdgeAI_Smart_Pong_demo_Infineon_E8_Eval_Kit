# Restore Points (Golden / Failsafe)

This repo uses two tags to mark known recoverable firmware states:

- `golden-e8-smart-pong`
- `failsafe-e8-smart-pong`

Both tags are intended to point to a verified build+flash commit.

## Current Tagged Baseline Intent

Current baseline includes:
- Direct-to-game startup (no `SMART PONG` splash title phase)
- `EDGEAI_FIXED_FPS=180`
- Higher gameplay pace with max ball speed cap tuned to `+50%` over prior baseline
- Verified build/program on `KIT_PSE84_EVAL_EPC2` with `CONFIG_DISPLAY=W4P3INCH_DISP`

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
