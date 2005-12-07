/**
 * @file logger.h
 *
 * @brief Interface of logger_t.
 *
 */

/*
 * Copyright (C) 2005 Jan Hutter, Martin Willi
 * Hochschule fuer Technik Rapperswil
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <stdio.h>

#include <types.h>


typedef enum logger_level_t logger_level_t;

/**
 * @brief Log Levels supported by the logger object.
 * 
 * Logleves are devided in two different kinds:
 * - levels to specify the type of the log
 * - levels to specify the detail-level of the log
 * 
 * Use combinations of these to build detailed loglevels, such
 * as CONTROL|MORE fore a detailed cotrol level, or
 * use RAW to see all raw data dumps (except private).
 * 
 * @ingroup utils
 */
enum logger_level_t {
	/**
	 * Control flow.
	 */
	CONTROL = 1,
	/**
	 * Error reporting.
	 */
	ERROR = 2,
	/**
	 * Logs important for the sysadmin.
	 */
	AUDIT = 4,
	/**
	 * Raw data dumps.
	 */
	RAW = 8,
	/**
	 * Private data dumps.
	 */
	PRIVATE = 16,
	
	/**
	 * Log most important output, can be omitted.
	 */
	LEVEL0 = 0,
	/**
	 * Log more detailed output.
	 */
	LEVEL1 = 32, 
	/**
	 * Log even more detailed output.
	 */
	LEVEL2 = LEVEL1 + 64,
	/**
	 * Use maximum detailed output.
	 */
	LEVEL3 = LEVEL2 + 128,
	
	/**
	 * Summary for all types with all detail-levels.
	 */
	FULL = LEVEL3 + CONTROL + ERROR + RAW + PRIVATE + AUDIT
};

typedef struct logger_t logger_t;

/**
 * @brief Class to simplify logging.
 * 
 * @b Constructors:
 *  - logger_create()
 * 
 * @ingroup utils
 */
struct logger_t {

	/**
	 * @brief Log an entry, using printf()-like params.
	 *
	 * All specified loglevels must be activated that
	 * the log is done.
	 *
	 * @param this 		logger_t object
	 * @param loglevel 	or'ed set of logger_level_t's
	 * @param format 	printf like format string
	 * @param ... 		printf like parameters
	 */
	void (*log) (logger_t *this, logger_level_t log_level, char *format, ...);

	/**
	 * @brief Log some bytes, useful for debugging.
	 *
	 * All specified loglevels must be activated that
	 * the log is done.
	 *
	 * @param this 		logger_t object
	 * @param loglevel 	or'ed set of logger_level_t's
	 * @param label 	a labeling name, logged with the bytes
	 * @param bytes 	pointer to the bytes to dump
	 * @param len	 	number of bytes to dump
	 */
	void (*log_bytes) (logger_t *this, logger_level_t loglevel, char *label, char *bytes, size_t len);

	/**
	 * @brief Log a chunk, useful for debugging.
	 *
	 * All specified loglevels must be activated that
	 * the log is done.
	 *
	 * @param this 		logger_t object
	 * @param loglevel 	or'ed set of logger_level_t's
	 * @param label 	a labeling name, logged with the bytes
	 * @param chunk		pointer to a chunk to log
	 */
	void (*log_chunk) (logger_t *this, logger_level_t loglevel, char *label, chunk_t *chunk);

	/**
	 * @brief Enables a loglevel for the current logger_t object.
	 *
	 * @param 			this logger_t object
	 * @param 			log_level loglevel to enable
	 */
	void (*enable_level) (logger_t *this, logger_level_t log_level);

	/**
	 * @brief Disables a loglevel for the current logger_t object.
	 *
	 * @param 			this logger_t object
	 * @param 			log_level loglevel to enable
	 */
	void (*disable_level) (logger_t *this, logger_level_t log_level);

	/**
	 * @brief Destroys a logger_t object.
	 *
	 * @param this		logger_t object
	 */
	void (*destroy) (logger_t *this);
};

/**
 * @brief Constructor to create a logger_t object.
 *
 * @param logger_name 	name for the logger_t object
 * @param log_level		or'ed set of log_levels to assign to the new logger_t object
 * @param log_thread_id	TRUE if thread id should also be logged
 * @param output		FILE * if log has to go on a file output, NULL for syslog
 * @return 				logger_t object 
 * 
 * @ingroup utils
 */
logger_t *logger_create(char *logger_name, logger_level_t log_level, bool log_thread_id, FILE * output);


#endif /*LOGGER_H_*/
