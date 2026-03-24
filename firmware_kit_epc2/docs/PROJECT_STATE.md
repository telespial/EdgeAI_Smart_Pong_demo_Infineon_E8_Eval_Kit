# PROJECT_STATE

## Project
PSOC Edge E84 Eval (EPC2), LVGL graphics base for Smart Pong port.

## Date
2026-03-24

## Working Hardware
- Kit: `KIT_PSE84_EVAL_EPC2`
- MCU detected during flash: `PSE846GPS2DBZC4A`
- Display: Waveshare 4.3-inch DSI panel on `J39`

## Build Configuration
- `TARGET=KIT_PSE84_EVAL_EPC2`
- `TOOLCHAIN=GCC_ARM`
- `CONFIG_DISPLAY=W4P3INCH_DISP`
- `APP_SMART_PONG_MODE=1` (golden active mode)
- Build guard enabled: non-`W4P3INCH_DISP` configs fail immediately in `proj_cm55/Makefile`

## Firmware State
- Build and program path verified with OpenOCD + KitProg3
- Latest visible behavior: centered `SMART`/`PONG` banner, then gameplay
- Smart Pong app path: `proj_cm55/app/EdgeAI_Smart_Pong_demo_Infineon_E8_Eval_Kit/`
- Full project rebuild/program verified after gameplay tuning, audio, and input updates
- Current tuning validated on hardware:
  - `EDGEAI_FIXED_FPS=180`
  - Max ball speed cap increased by `+50%` over prior baseline
  - Audio events mapped: wall `226 Hz`, paddle `459 Hz`, point `490 Hz`, win tune
  - Volume control range `0..100`, boot default `60`, settings row `VOL DN  xxx  UP`
  - CapSense volume path implemented in input HAL (I2C status + GPIO fallback)
  - Aggressive AI lead/chase retune with reduced EdgeAI noise
  - Easy-ball lock enabled (close-range analytic intercept to prevent simple misses)
  - Local build exclusion for parallel insulin app folder to keep Pong release path clean

## Recent Changes
1. Raised fixed-step loop target from `60` to `180` FPS.
2. Increased global ball speed cap by `+50%`.
3. Reworked boot banner to simple two-line `SMART`/`PONG`.
4. Added event audio + win tune and runtime volume control in settings.
5. Added volume event path (`VOL DN`/`VOL UP`) through input HAL.
6. Rebuilt and programmed successfully on E8 EPC2 + 4.3-inch display profile.
7. Removed 10.1/alternate display path from active build and touch HAL routing.
8. Added multiple AI lead/chase tuning passes with hardware validation flashes.
9. Added easy-ball lock logic to cut close-range misses.
10. Excluded parallel insulin app folder from CM55 build via `CY_IGNORE` in `proj_cm55/Makefile`.
11. Fairness retune in `game/ai.c` to reduce fixed mixed-mode EdgeAI pre-bias while preserving adaptive learning improvements:
    - Reduced fixed EdgeAI lead bonus.
    - Reduced fixed trailing catch-up amplification.
    - Reduced fixed mixed-mode noise-reduction boosts.
12. Build and flash re-run after fairness retune with full toolchain environment configured:
    - `make build TOOLCHAIN=GCC_ARM CONFIG_DISPLAY=W4P3INCH_DISP -j8` ✅
    - `make program TOOLCHAIN=GCC_ARM CONFIG_DISPLAY=W4P3INCH_DISP` ✅
    - Hardware/programming confirmation:
      - Device: `PSE846GPS2DBZC4A` (Rev `B0`)
      - Programmed: `app_combined.hex`
      - Flash write/verify completed successfully.
13. Created timestamped restore artifacts for Golden/Failsafe release capture:
    - `../failsafe/e8_smart_pong_20260324_081904_fairness_retune_app_combined.hex`
    - `../failsafe/e8_smart_pong_20260324_081904_fairness_retune_proj_cm55.elf`

## Next Milestones
1. Complete end-to-end validation for CS81/CS82 touch path with bridge firmware state.
2. Continue gameplay polish and render artifact hardening under high speed.
3. Keep 4.3-inch EPC2 path as the only supported and release-pinned target.
