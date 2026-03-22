# PROJECT_STATE

## Project
PSOC Edge E84 Eval (EPC2), LVGL graphics base for Smart Pong port.

## Date
2026-03-22

## Working Hardware
- Kit: `KIT_PSE84_EVAL_EPC2`
- MCU detected during flash: `PSE846GPS2DBZC4A`
- Display: Waveshare 4.3-inch DSI panel on `J39`

## Build Configuration
- `TARGET=KIT_PSE84_EVAL_EPC2`
- `TOOLCHAIN=GCC_ARM`
- `CONFIG_DISPLAY=W4P3INCH_DISP`
- `APP_SMART_PONG_MODE=1` (golden active mode)

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

## Recent Changes
1. Raised fixed-step loop target from `60` to `180` FPS.
2. Increased global ball speed cap by `+50%`.
3. Reworked boot banner to simple two-line `SMART`/`PONG`.
4. Added event audio + win tune and runtime volume control in settings.
5. Added volume event path (`VOL DN`/`VOL UP`) through input HAL.
6. Rebuilt and programmed successfully on E8 EPC2 + 4.3-inch display profile.

## Next Milestones
1. Complete end-to-end validation for CS81/CS82 touch path with bridge firmware state.
2. Continue gameplay polish and render artifact hardening under high speed.
3. Keep 4.3-inch as baseline while preserving optional 10.1-inch build path.
