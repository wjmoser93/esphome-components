import gzip
import json
import yaml
import requests
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import web_server_base
from esphome.components.web_server_base import CONF_WEB_SERVER_BASE_ID
from esphome.const import (
    CONF_CSS_INCLUDE,
    CONF_CSS_URL,
    CONF_ID,
    CONF_JS_INCLUDE,
    CONF_JS_URL,
    CONF_ENABLE_PRIVATE_NETWORK_ACCESS,
    CONF_PORT,
    CONF_AUTH,
    CONF_USERNAME,
    CONF_PASSWORD,
    CONF_INCLUDE_INTERNAL,
    CONF_OTA,
    CONF_LOG,
    CONF_VERSION,
    CONF_LOCAL,
    PLATFORM_ESP32,
    PLATFORM_ESP8266,
    PLATFORM_BK72XX,
    PLATFORM_RTL87XX,
)
from esphome.core import CORE, coroutine_with_priority

AUTO_LOAD = ["json", "web_server_base"]

CONF_CONFIG ="config_local"
CONF_KEYPAD_URL="config_url"
CONF_PARTITIONS="partitions"
CONF_SERVICE_LAMBDA="service_lambda"

web_server_ns = cg.esphome_ns.namespace("web_server")
WebServer = web_server_ns.class_("WebServer", cg.Component, cg.Controller)


def default_url(config):
    config = config.copy()
    if config[CONF_VERSION] == 1:
        if not (CONF_CSS_URL in config):
            config[CONF_CSS_URL] = "https://esphome.io/_static/webserver-v1.min.css"
        if not (CONF_JS_URL in config):
            config[CONF_JS_URL] = "https://esphome.io/_static/webserver-v1.min.js"
    if config[CONF_VERSION] == 2:
        if not (CONF_CSS_URL in config):
            config[CONF_CSS_URL] = ""
        if not (CONF_JS_URL in config):
            config[CONF_JS_URL] = "https://oi.esphome.io/v2/www.js"
    return config


def validate_local(config):
    if CONF_LOCAL in config and config[CONF_VERSION] == 1:
        raise cv.Invalid("'local' is not supported in version 1")
    return config


def validate_ota(config):
    if CORE.using_esp_idf and config[CONF_OTA]:
        raise cv.Invalid("Enabling 'ota' is not supported for IDF framework yet")
    return config


CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(WebServer),
            cv.Optional(CONF_PORT, default=80): cv.port,
            cv.Optional(CONF_VERSION, default=2): cv.one_of(1,2, int=True),
            cv.Optional(CONF_CSS_URL): cv.string,
            cv.Optional(CONF_CSS_INCLUDE): cv.file_,
            cv.Optional(CONF_JS_URL): cv.string,
            cv.Optional(CONF_PARTITIONS): cv.int_,            
            cv.Optional(CONF_JS_INCLUDE): cv.file_,
            cv.Optional(CONF_CONFIG):cv.file_,
            cv.Optional(CONF_KEYPAD_URL):cv.string,  
            cv.Optional(CONF_SERVICE_LAMBDA): cv.lambda_,
            cv.Optional(CONF_ENABLE_PRIVATE_NETWORK_ACCESS, default=True): cv.boolean,
            cv.Optional(CONF_AUTH): cv.Schema(
                {
                    cv.Required(CONF_USERNAME): cv.All(
                        cv.string_strict, cv.Length(min=1)
                    ),
                    cv.Required(CONF_PASSWORD): cv.All(
                        cv.string_strict, cv.Length(min=1)
                    ),
                }
            ),
            cv.GenerateID(CONF_WEB_SERVER_BASE_ID): cv.use_id(
                web_server_base.WebServerBase
            ),
            cv.Optional(CONF_INCLUDE_INTERNAL, default=False): cv.boolean,
            cv.SplitDefault(
                CONF_OTA,
                esp8266=True,
                esp32_arduino=True,
                esp32_idf=False,
                bk72xx=True,
                rtl87xx=True,
            ): cv.boolean,
            cv.Optional(CONF_LOG, default=True): cv.boolean,
            cv.Optional(CONF_LOCAL): cv.boolean,
        }
    ).extend(cv.COMPONENT_SCHEMA),
    cv.only_on([PLATFORM_ESP32, PLATFORM_ESP8266, PLATFORM_BK72XX, PLATFORM_RTL87XX]),
    default_url,
    validate_local,
    validate_ota,
)


@coroutine_with_priority(40.0)
async def to_code(config):
    paren = await cg.get_variable(config[CONF_WEB_SERVER_BASE_ID])
    cg.add_library("WiFi", None)
    cg.add_library("FS", None)
    cg.add_library("Update", None)
    #var = cg.new_Pvariable(config[CONF_ID], paren)
    var = cg.new_Pvariable(config[CONF_ID])    
    await cg.register_component(var,config)
    cg.add_library("https://github.com/jeremypoulter/ArduinoMongoose.git", None) 


         

