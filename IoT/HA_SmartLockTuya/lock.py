"""Platform for lock integration."""
import logging
from tuya_connector import (
    TuyaOpenAPI,
    TuyaOpenPulsar,
    TuyaCloudPulsarTopic,
    TUYA_LOGGER,
)


import voluptuous as vol
import pkg_resources
from pkg_resources import parse_version
from threading import Thread
from time import perf_counter
import homeassistant.exceptions
import homeassistant.helpers.config_validation as cv
from homeassistant.core import callback
from homeassistant.helpers.event import async_call_later
# Import the device class from the component that you want to support
from homeassistant.components.lock import PLATFORM_SCHEMA, SUPPORT_OPEN, LockEntity
from homeassistant.const import ATTR_BATTERY_LEVEL, ATTR_ID, CONF_ACCESS_TOKEN, STATE_LOCKED, STATE_UNLOCKED
from .const import (
    DOMAIN,
    NAME,
    SCAN_INTERVAL
)

from datetime import timedelta

ATTR_CONNECTED = "connected"
ATTR_ENDPOINT = "https://openapi.tuyaeu.com"
ATTR_MQ_ENDPOINT = "wss://mqe.tuyaeu.com:8285/"
ATTR_ALARM = "alarm_notification"
CONF_ACCESS_KEY = "access_key"
CONF_ACCESS_ID = "access_id"

SCAN_INTERVAL = timedelta(seconds=10)
DOMAIN = "tuya_door_lock"
ATTR_DOMAIN = DOMAIN
EVENT_DOOR_BELL = ATTR_DOMAIN+"_event"


_LOGGER = logging.getLogger(__name__)


# Validation of the user's configuration
PLATFORM_SCHEMA = PLATFORM_SCHEMA.extend({
    vol.Required(CONF_ACCESS_KEY, default='no access token given'): cv.string,
    vol.Required(CONF_ACCESS_ID, default='no access token given'): cv.string,
})


def on_message(self, msg):
    """Handle automation trigger service calls."""
    # 1. Door bell:
        event_data = {
            ATTR_ID: "my-device-id", # Lock
            ATTR_ALARM: True
        }
        hass.bus.async_fire(EVENT_DOOR_BELL, event_data)


async def async_setup_entry(hass, config, async_add_entities):
    id  = config.data.get(CONF_ACCESS_ID)
    key = config.data.get(CONF_ACCESS_KEY)

    try:
        tuya_lock = await hass.async_add_executor_job(lambda : tuyaAPIInitLock(id, key))
    except TedeeClientException as exc:
        _LOGGER.error(exc)
        return
    _LOGGER.debug("available_locks: %s", len(tuya_lock))

    if len(tuya_lock) == 0:
        # No locks found; abort setup routine.
        _LOGGER.info("No locks found in your account")
        return


    tuya_lock["obj"].token_info.expire_time = 0

    _lockmq = TuyaOpenMQ(tuya_lock["obj"])
    _lockmq.start()
    # Create thread
    thread = Thread(target=_lockmq.add_message_listener, args=on_message)
    thread.start()

    async_add_entities([[TuyaLock(tuya_lock) for lock in tuya_lock], True)

# Should return locks device ID
# List of dict locks = [ lock_dict, lock2_dict], each dict will contain some attributes
async def tuyaAPIInitLock(access_id, access_key):
    pass


class TuyaLock(LockEntity):
    """Representation of a Tuya door  lock."""

    def __init__(self, tuya_lock):
        _LOGGER.debug("LockEntity: %s", tuya_lock.get_name())
        """Initialize the lock."""
        self._lock = tuya_lock["obj"]           # openapi object
        self._lock_id = tuya_lock["device_id"]
        self._battery_level = tuya_lock["battery_level"]
        self._available = tuya_lock["available"] # True or False
        self._door_bell_exist = False
        self._alarm_exist = False
        self._lock_name = tuya_lock["lock_name"]
        self._features_list = tuya_lock["features"]



    @property
    def supported_features(self):
        """Flag supported features."""
        return self._features_list

    @property
    def available(self) -> bool:
        """Return True if entity is available."""
        return self._available

    def update(self):
        self._available = self.get_status()
        self._battery_level = self.get_battery_level()

    @property
    def name(self):
        """Return the name of the lock."""
        name = self._lock.get_name()
        return name

    @property
    def extra_state_attributes(self):
        # Call an update to the status first
        return {
            ATTR_ID: self._lock_id,

            ATTR_BATTERY_LEVEL: self._battery_level,

            ATTR_CONNECTED: self._available,

            ATTR_ALARM: self._alarm_exist
        }


    @property
    def device_id(self):
        return self._lock_id

    @property
    def unlock(self):
        """Unlock the door."""
        return_code = self._lock.post("/v1.0/devices/{}/door-lock/password-ticket".format(self._lock_id))
        ticket_id = return_code['result']["ticket_id"]
        ticket_key = return_code['result']["ticket_key"]
        commands = {'ticket_id': ticket_id, }
        return_code = self._locks.post("/v1.0/devices/{}/door-lock/password-free/open-door".format(self._lock_id), commands)
        _LOGGER.info("Door was unlocked, return code: %s", return_code)

    # def _update_handler(self):
    #     if self._door_bell_exist:
    #         self.unlock()
    #     elif self._alarm:
    #         self.generateAlarm()
    #
    # async def async_added_to_hass(self) -> None:
    #     self.hass.bus.async_listen(EVENT_DOOR_BELL, self._update_handler)

    @property
    def device_info(self):
        # Call an update first
        return {
            "identifiers": {
                (ATTR_DOMAIN, self._lock_id)
            },
            "name": self._lock_name,
        }

    def async_update(self):

        ''' Perform some update call to the could '''

        self.get_status()
        self.get_battery_level()
        self.async_schedule_update_ha_state(True)

    ''' Helper Functions'''
    def parse_response(self, attribute):
        # GET


        # Pars based on attrribute
        pass

    def get_status(self):
        res = parse_response("status")
        pass

    def get_battery_level(self):
        res = parse_response("battery_level")
        pass