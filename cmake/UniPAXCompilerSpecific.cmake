SET(UNIPAX_COMPILER_FLAGS)
SET(UNIPAX_LINKER_FLAGS)

SET(UNIPAX_COMPILER_IS_GNUCXX ${CMAKE_COMPILER_IS_GNUCXX})
SET(UNIPAX_COMPILER_IS_MSVC ${CMAKE_COMPILER_IS_MSVC})

IF(CMAKE_COMPILER_IS_GNUCXX)
	# -fvisibility=hidden: Symbols which should be accessable from outside the library
	#                      must be explicitly declared as visible. This is similar to
	#                      the default behaviour on windows
	# -pedantic:           Check for  ISO C++ compatible code
	SET(UNIPAX_COMPILE_FLAGS "-Wno-long-long -pedantic -fvisibility=hidden")

	# -Wl,--as-needed:     Tell the linker to only pull in shared object as dependency
	#                      when a symbol from it is used in the compiled code
	SET(UNIPAX_LINK_FLAGS "-Wl,--as-needed")
ENDIF()
