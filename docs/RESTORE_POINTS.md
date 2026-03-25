# Restore Points (Golden + Failsafe)

## Current Golden
- Rolling tag: `golden-e8-smart-pong`
- Dated tag: `golden-e8-smart-pong-20260325`
- Date: `2026-03-25`
- Commit: `eee3ff9` (plus this docs sync commit)
- Verified on hardware with build + flash.

## Current Failsafe
- Rolling tag: `failsafe-e8-smart-pong`
- Dated tag: `failsafe-e8-smart-pong-20260325`
- Purpose: fast rollback point if active development breaks boot/display/flash.

## Restore
```bash
git fetch --tags
git checkout golden-e8-smart-pong
# or
git checkout failsafe-e8-smart-pong
```

## Validation rule
Only create or move restore tags after successful build and flash on target hardware.
