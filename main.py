import json
from Src.Boards.RaspberryPi.Pico_W import generate_pico_w_cpp


CONFIGURATION_FILE_NAME: str = 'BroadBoard.json'


BOARD_MAPPING = {
    'RaspberryPi:Pico-W': {
        'C++': generate_pico_w_cpp
    }
}


def main():
    with open(CONFIGURATION_FILE_NAME) as f:
        config_file = json.load(f)
        board_name: str = config_file['board']
        language: str = config_file['language']

        if board_name in BOARD_MAPPING and language in BOARD_MAPPING[board_name]:
            BOARD_MAPPING[board_name][language](config_file)
        else:
            print('ERROR')
