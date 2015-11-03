/** @file crt0.S
 *
 * @brief Execution startup routine
 *
 * @author Mike Kasick <mkasick@andrew.cmu.edu>
 * @date   Sun, 07 Oct 2007 01:51:29 -0400
 */

#include <asm.h>
#include <bits/swi.h>

	.file "crt0.S"

FUNC(_start)

	LDMFD	sp!, {r0-r1}	@load arc and argv into r0 and r1
	bl 		main			@branch to main function
	swi 	EXIT_SWI	@exit swi after return from branch
