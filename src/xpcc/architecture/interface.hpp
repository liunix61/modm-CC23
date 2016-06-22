// coding: utf-8
/* Copyright (c) 2013, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------

#ifndef XPCC_INTERFACE_HPP
#define XPCC_INTERFACE_HPP

#include <stdint.h>
#include <cstddef>
#include <xpcc/math/tolerance.hpp>

/**
 * @ingroup 	architecture
 * @defgroup	interface	Architecture Interfaces
 *
 * All hardware peripherals with common interfaces.
 */

namespace xpcc
{

/**
 * Peripheral class
 *
 * This class acts as a base class for all classes describing the
 * public interface of common peripheral drivers.
 * As there is no implementation given, the classes specific to the platform
 * inherit from their respective base classes and must shadow the methods of
 * them.
 *
 * The inheritance is only visible for the documentation, it is completely
 * removed during compile time keeping a possible error at platform level.
 * This is safe, because only one platform can be compiled at once.
 *
 * This way, no virtual functions are needed and no overhead is generated,
 * but we still have clean inheritance in the documentation.
 * There is no need to document the platform specific implementation, since
 * it is taken from the base class.
 *
 * @ingroup peripheral
 * @author	Niklas Hauser
 */
class Peripheral
{
#ifdef __DOXYGEN__
	/// @cond
	/// initializes the peripheral, must be called before use.
	static void
	initialize();

	/// configures a peripheral for a specific purpose
	static void
	configurePurpose();

	/// sets a parameter
	static void
	setParameter();

	/// returns a parameter
	static void
	getParameter();

	/// Read an interrupt flag.
	static bool
	getInterruptFlag();

	/**
	 * Acknowledge an interrupt flag.
	 *
	 * We use acknowledge here, since it describes the intention rather
	 * than the actual implementation.
	 */
	static void
	acknowledgeInterruptFlag();
	/// @endcond
#endif

public:
	/**
	 * Since baudrates are usually generated by prescaling a system clock,
	 * only several distinct values can be generated.
	 * This method checks if the user requested baudrate is within error
	 * tolerance of the system achievable baudrate.
	 */
	template< uint32_t available, uint32_t requested, uint16_t tolerance >
	static void
	assertBaudrateInTolerance()
	{
		static_assert(xpcc::Tolerance::isValueInTolerance(requested, available, tolerance),
				"The closest available baudrate exceeds the tolerance of the requested baudrate!");
	}
};

} // namespace xpcc

#include "interface/can.hpp"
#include "interface/gpio.hpp"
#include "interface/uart.hpp"
#include "interface/one_wire.hpp"
#include "interface/spi.hpp"
#include "interface/i2c.hpp"
#include "interface/register.hpp"
#include "interface/memory.hpp"

#endif	// XPCC_INTERFACE_HPP
