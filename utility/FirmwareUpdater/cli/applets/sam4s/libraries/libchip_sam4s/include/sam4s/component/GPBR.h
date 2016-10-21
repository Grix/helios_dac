/* %ATMEL_LICENCE% */

#ifndef _SAM4S_GPBR_COMPONENT_
#define _SAM4S_GPBR_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR General Purpose Backup Register */
/* ============================================================================= */
/** \addtogroup SAM4S_GPBR General Purpose Backup Register */
/*@{*/

#ifndef __ASSEMBLY__
/** \brief Gpbr hardware registers */
typedef struct {
  RwReg SYS_GPBR0; /**< \brief (Gpbr Offset: 0x0) General Purpose Backup Register 0 */
  RwReg SYS_GPBR1; /**< \brief (Gpbr Offset: 0x4) General Purpose Backup Register 1 */
  RwReg SYS_GPBR2; /**< \brief (Gpbr Offset: 0x8) General Purpose Backup Register 2 */
  RwReg SYS_GPBR3; /**< \brief (Gpbr Offset: 0xC) General Purpose Backup Register 3 */
  RwReg SYS_GPBR4; /**< \brief (Gpbr Offset: 0x10) General Purpose Backup Register 4 */
  RwReg SYS_GPBR5; /**< \brief (Gpbr Offset: 0x14) General Purpose Backup Register 5 */
  RwReg SYS_GPBR6; /**< \brief (Gpbr Offset: 0x18) General Purpose Backup Register 6 */
  RwReg SYS_GPBR7; /**< \brief (Gpbr Offset: 0x1C) General Purpose Backup Register 7 */
} Gpbr;
#endif /* __ASSEMBLY__ */
/* -------- SYS_GPBR0 : (GPBR Offset: 0x0) General Purpose Backup Register 0 -------- */
#define SYS_GPBR0_GPBR_VALUE0_Pos 0
#define SYS_GPBR0_GPBR_VALUE0_Msk (0xffffffffu << SYS_GPBR0_GPBR_VALUE0_Pos) /**< \brief (SYS_GPBR0) Value of GPBR x */
#define SYS_GPBR0_GPBR_VALUE0(value) ((SYS_GPBR0_GPBR_VALUE0_Msk & ((value) << SYS_GPBR0_GPBR_VALUE0_Pos)))
/* -------- SYS_GPBR1 : (GPBR Offset: 0x4) General Purpose Backup Register 1 -------- */
#define SYS_GPBR1_GPBR_VALUE1_Pos 0
#define SYS_GPBR1_GPBR_VALUE1_Msk (0xffffffffu << SYS_GPBR1_GPBR_VALUE1_Pos) /**< \brief (SYS_GPBR1) Value of GPBR x */
#define SYS_GPBR1_GPBR_VALUE1(value) ((SYS_GPBR1_GPBR_VALUE1_Msk & ((value) << SYS_GPBR1_GPBR_VALUE1_Pos)))
/* -------- SYS_GPBR2 : (GPBR Offset: 0x8) General Purpose Backup Register 2 -------- */
#define SYS_GPBR2_GPBR_VALUE2_Pos 0
#define SYS_GPBR2_GPBR_VALUE2_Msk (0xffffffffu << SYS_GPBR2_GPBR_VALUE2_Pos) /**< \brief (SYS_GPBR2) Value of GPBR x */
#define SYS_GPBR2_GPBR_VALUE2(value) ((SYS_GPBR2_GPBR_VALUE2_Msk & ((value) << SYS_GPBR2_GPBR_VALUE2_Pos)))
/* -------- SYS_GPBR3 : (GPBR Offset: 0xC) General Purpose Backup Register 3 -------- */
#define SYS_GPBR3_GPBR_VALUE3_Pos 0
#define SYS_GPBR3_GPBR_VALUE3_Msk (0xffffffffu << SYS_GPBR3_GPBR_VALUE3_Pos) /**< \brief (SYS_GPBR3) Value of GPBR x */
#define SYS_GPBR3_GPBR_VALUE3(value) ((SYS_GPBR3_GPBR_VALUE3_Msk & ((value) << SYS_GPBR3_GPBR_VALUE3_Pos)))
/* -------- SYS_GPBR4 : (GPBR Offset: 0x10) General Purpose Backup Register 4 -------- */
#define SYS_GPBR4_GPBR_VALUE4_Pos 0
#define SYS_GPBR4_GPBR_VALUE4_Msk (0xffffffffu << SYS_GPBR4_GPBR_VALUE4_Pos) /**< \brief (SYS_GPBR4) Value of GPBR x */
#define SYS_GPBR4_GPBR_VALUE4(value) ((SYS_GPBR4_GPBR_VALUE4_Msk & ((value) << SYS_GPBR4_GPBR_VALUE4_Pos)))
/* -------- SYS_GPBR5 : (GPBR Offset: 0x14) General Purpose Backup Register 5 -------- */
#define SYS_GPBR5_GPBR_VALUE5_Pos 0
#define SYS_GPBR5_GPBR_VALUE5_Msk (0xffffffffu << SYS_GPBR5_GPBR_VALUE5_Pos) /**< \brief (SYS_GPBR5) Value of GPBR x */
#define SYS_GPBR5_GPBR_VALUE5(value) ((SYS_GPBR5_GPBR_VALUE5_Msk & ((value) << SYS_GPBR5_GPBR_VALUE5_Pos)))
/* -------- SYS_GPBR6 : (GPBR Offset: 0x18) General Purpose Backup Register 6 -------- */
#define SYS_GPBR6_GPBR_VALUE6_Pos 0
#define SYS_GPBR6_GPBR_VALUE6_Msk (0xffffffffu << SYS_GPBR6_GPBR_VALUE6_Pos) /**< \brief (SYS_GPBR6) Value of GPBR x */
#define SYS_GPBR6_GPBR_VALUE6(value) ((SYS_GPBR6_GPBR_VALUE6_Msk & ((value) << SYS_GPBR6_GPBR_VALUE6_Pos)))
/* -------- SYS_GPBR7 : (GPBR Offset: 0x1C) General Purpose Backup Register 7 -------- */
#define SYS_GPBR7_GPBR_VALUE7_Pos 0
#define SYS_GPBR7_GPBR_VALUE7_Msk (0xffffffffu << SYS_GPBR7_GPBR_VALUE7_Pos) /**< \brief (SYS_GPBR7) Value of GPBR x */
#define SYS_GPBR7_GPBR_VALUE7(value) ((SYS_GPBR7_GPBR_VALUE7_Msk & ((value) << SYS_GPBR7_GPBR_VALUE7_Pos)))

/*@}*/


#endif /* _SAM4S_GPBR_COMPONENT_ */
