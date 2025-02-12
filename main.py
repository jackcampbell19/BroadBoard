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
        'languages': {
            'C++': 'Src/Boards/RaspberryPi/BroadBoard.cpp'
        },
    },
    'Teensy:4.1': {
        'pinout': TEENSY41_PIN_MAPPING,
        'languages': {
            'C++': 'Src/Boards/Teensy/BroadBoard.cpp'
        }
    }
}


def generate_cpp(config_file, pin_mapping, board):

    install_path: Path = Path(config_file['path'])

    prefix: str = 'inline static'

    pin_definitions = []
    for pin in config_file['pinout']:
        definition = config_file['pinout'][pin]
        pin_name: str = definition['name']
        pin_type: str = definition['type']

        if pin_type == 'output':
            pin_definitions.append(
                f"{prefix} OutputPin {pin_name}{'{'}{pin_mapping[pin]}{'}'};"
            )

        elif pin_type == 'input':
            resistor: str = 'InputResistor::DISABLED'
            if 'resistor' in definition:
                if definition['resistor'] == 'pull_up':
                    resistor = 'InputResistor::PULL_UP'
                elif definition['resistor'] == 'pull_down':
                    resistor = 'InputResistor::PULL_DOWN'
            pin_definitions.append(
                f"{prefix} InputPin {pin_name}{'{'}{pin_mapping[pin]}, {resistor}{'}'};"
            )

        elif pin_type == 'adc':
            pass

        elif pin_type == 'uart':
            pass

    with open(Path(__file__).parent / Path('Src/BroadBoard.h'), 'r') as f:
        contents = f.read()
        f.close()

        composed_pin_definitions = ''
        for definition in pin_definitions:
            composed_pin_definitions += f"        {definition}\n"

        contents = contents.replace('<BROAD-BOARD-DEFINITIONS>', composed_pin_definitions)

        if not install_path.exists():
            os.makedirs(install_path, exist_ok=True)

        with open(install_path / Path('BroadBoard.h'), 'w') as install_file:
            install_file.write(contents)

        shutil.copy2(Path(__file__).parent / Path(board['languages']['C++']), install_path / Path('BroadBoard.cpp'))


def main():
    with open(CONFIGURATION_FILE_NAME, 'r') as f:
        config_file = json.load(f)
        board_name: str = config_file['board']
        language: str = config_file['language']

        if board_name in BOARD_MAPPING and language in BOARD_MAPPING[board_name]['languages']:
            generate_cpp(config_file, BOARD_MAPPING[board_name]['pinout'], BOARD_MAPPING[board_name])
        else:
            print('ERROR')


if __name__ == '__main__':
    main()
