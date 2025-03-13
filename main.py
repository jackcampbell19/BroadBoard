import json
from Src.Boards.RaspberryPi.Pico_W import PICO_W_PIN_MAPPING
from Src.Boards.Teensy.Teensy41 import TEENSY41_PIN_MAPPING
import os
from pathlib import Path
import shutil


CONFIGURATION_FILE_NAME: str = 'BroadBoard.json'


BOARD_MAPPING = {
    'RaspberryPi:Pico-W': {
        'pinout': PICO_W_PIN_MAPPING,
        'languages': [
            'C++'
        ],
    },
    'Teensy:4.1': {
        'pinout': TEENSY41_PIN_MAPPING,
        'sources': 'Sources/CPP/Boards/Teensy/41',
        'languages': [
            'C++'
        ]
    }
}


def generate_cpp(config_file, board_identifier: str):

    # Get pin mapping for the specific board
    pin_mapping = BOARD_MAPPING[board_identifier]['pinout']

    # Set install path for the BoardBoard content
    install_path: Path = Path(config_file['path'])

    # Define the pin definitions for BroadBoard.h
    pin_definition_prefix: str = 'inline static'
    pin_definitions = []
    for pin in pin_mapping:
        definition = pin_mapping[pin]
        pin_name: str = definition['name']
        pin_type: str = definition['type']

        # Define output pin
        if pin_type == 'output':
            pin_definitions.append(
                f"{pin_definition_prefix} OutputPin {pin_name}{'{'}{pin_mapping[pin]}{'}'};"
            )

        # Define input pin
        elif pin_type == 'input':
            resistor: str = 'InputResistor::DISABLED'
            if 'resistor' in definition:
                if definition['resistor'] == 'pull_up':
                    resistor = 'InputResistor::PULL_UP'
                elif definition['resistor'] == 'pull_down':
                    resistor = 'InputResistor::PULL_DOWN'
            pin_definitions.append(
                f"{pin_definition_prefix} InputPin {pin_name}{'{'}{pin_mapping[pin]}, {resistor}{'}'};"
            )

        # Define ADC pin
        elif pin_type == 'adc':
            pass

        # Define UART pin
        elif pin_type == 'uart':
            pass

    # Create BroadBoard.h file within the target directory
    with open(Path(__file__).parent / Path('Sources/CPP/Core/BroadBoard.h'), 'r') as f:
        contents = f.read()
        f.close()

        # Compose string of pin definitions to interpolate into the BroadBoard file
        composed_pin_definitions: str = ''
        for definition in pin_definitions:
            composed_pin_definitions += f"        {definition}\n"

        # Replace placeholder with defined pins
        contents = contents.replace('<BROAD-BOARD-DEFINITIONS>', composed_pin_definitions)

        # Create the installation path
        if not install_path.exists():
            os.makedirs(install_path, exist_ok=True)

        # Write the BroadBoard.h file
        with open(install_path / Path('BroadBoard.h'), 'w') as install_file:
            install_file.write(contents)

    # Copy all the core files
    core_files = [
        'GPIO.h',
        'Logger.h'
        'Timing.h'
    ]
    for file in core_files:
        shutil.copy2(
            Path(__file__).parent / Path("Sources/CPP/Core") / Path(file),
            install_path / Path(file)
        )

    # Copy over board specific source files
    sources_path = BOARD_MAPPING[board_identifier]['sources']
    shutil.copy2(Path(__file__).parent / Path(sources_path) / Path('BoardBoard.cpp'), install_path / Path('BroadBoard.cpp'))


def main() -> int:

    # Open configuration file from the calling directory
    with open(CONFIGURATION_FILE_NAME, 'r') as f:
        config_file = json.load(f)

        # Get the board identifier and the desired language
        board_identifier: str = config_file['board']
        language: str = config_file['language']

        # Check if the board is supported
        if board_identifier not in BOARD_MAPPING:
            print(f"Invalid board identifier: {board_identifier}")
            return -1

        # Check if the language is supported
        if language not in BOARD_MAPPING[board_identifier]['languages']:
            print(f"Language is not supported on the provided board: {language}")
            return -1

        if language == 'C++':
            generate_cpp(config_file, board_identifier)

    return 0


if __name__ == '__main__':
    exit(main())
