# Coffee Machine Library Changelog

## []
### Added
- Added configurable max safe temperature to cut off the heater

### Removed
- Removed unused configuration parameters

## [0.3.0] - 24/03/2021
### Changed
- Serial interface output can now be configured to be on/off
- Added sample rate to the Relay Controller (compute every 100ms)
- Rename configuration SPI_DO_PIN to SPI_CS_PIN
- Moved default_configuration.h inside the default directory renaming it to configuration.h

### Added
- Added new method to the BaseDisplay interface to explicitly print the buffer to the display
- BaseDisplay interface allow definition of an optional custom print function
- Default PID controller implementation

### Fixed
- Serial baudrate configuration is now used to initialise the serial interface
- Display class calls the initialise() of the BaseDisplay instance during construction

## [0.2.0] - 24/02/2021
### Changed
- Simplified example of Adapter class
- Removed unused includes
- Updated README examples

## [0.1.0] - 11/02/2021
### Added
- Added missing include for std functions
- Updated CMake configuration adding install target
- Added run_tests target to run all unit tests
- First release:
  - Support for water and steam temperature sensor
  - Support for serial interface
  - Support for display
  - Support for single heater
  - Support for machine mode detector
