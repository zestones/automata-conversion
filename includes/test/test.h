#ifndef _TEST_H_
#define _TEST_H_

#include <stdio.h>
#include <stdlib.h>

#include "../afn/afn.h"
#include "../afd/afd.h"

// -------------------------------------------------------- //

/**
 * @brief Language reconnu : a
 *
 * @return AFN
 */
AFN creer_automate_simple_a();

/**
 * @brief Language reconnu : b*a+b
 *
 * @return AFN
 */
AFN creer_automate_simple_ab();

AFN creer_automate_complex_ab();

AFN creer_automate_complex_abc();

// -------------------------------------------------------- //

#endif