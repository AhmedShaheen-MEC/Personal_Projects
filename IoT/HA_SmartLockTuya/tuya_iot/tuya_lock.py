import logging
import TuyaOpenAPI, TUYA_LOGGER
import json
ENDPOINT = "https://openapi.tuyaeu.com"
LOCK_URL_PREFIX = '/v1.0/devices/iot-03/'
class TuyaLock():

    def __init__(self, end_point, end_point, access_key, schema):
        TUYA_LOGGER.setLevel(logging.DEBUG)
        self.__open_api = TuyaOpenAPI(end_point, end_point, access_key)
        self.__battery_level = 'low'
        self.__unlock_fingerprint = '0'
        self.__unlock_card = '0'
        self.__unlock_request = '0'
        self.__unlock_app = '0'
        self.__unlock_password = '0'
        self.__residual_electricity = '0'
        self.__lock_name = ""
        self.__lock_id = ""
    def get_open_api(self):
        pass

    def get_battery_level(self):
        return self.__battery_level

    def get_id(self):
        return self.__lock_id

    def update(self, lock_id):
        pass

    def get_state(self):
        pass

    def get_name(self):
        return self.__lock_name

    def set_temp_pass(self):
        pass

    def check_lock_alarm(self):
        pass

    def hijack_alarm(self):
        pass

    def get_lock_useres(self):
        pass

    def set_unlock_request(self):
        pass

    def reply_unlock_request(self):
        pass

    def latch_lock(self):
        pass

    def unlatch_lock(self):
        pass


class GetLockIDs():

    pass