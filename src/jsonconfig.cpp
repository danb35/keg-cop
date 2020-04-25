/* Copyright (C) 2019-2020 Lee C. Bussy (@LBussy)

This file is part of Lee Bussy's Keg Cop (keg-cop).

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

#include "jsonconfig.h"

const char *filename = "/config.json";
Config config;
extern const size_t capacityDeserial = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(7) + JSON_OBJECT_SIZE(9) + 820;
extern const size_t capacitySerial = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(7) + JSON_OBJECT_SIZE(9);

bool deleteConfigFile() {
    if (!SPIFFS.begin()) {
        return false;
    }
    return SPIFFS.remove(filename);
}

bool loadConfig()
{
    // Manage loading the configuration
    if (!loadFile()) {
        return false;
    } else {
        saveFile();
        return true;
    }
}

bool loadFile()
{
    if (!SPIFFS.begin()) {
        return false;
    }
    // Loads the configuration from a file on SPIFFS
    File file = SPIFFS.open(filename, "r");
    if (!SPIFFS.exists(filename) || !file) {
        // File does not exist or unable to read file
    } else {
        // Existing configuration present
    }

    if (!deserializeConfig(file)) {
        file.close();
        return false;
    } else {
        file.close();
        return true;
    }
}

bool saveConfig()
{
    return saveFile();
}

bool saveFile()
{
    // Saves the configuration to a file on SPIFFS
    File file = SPIFFS.open(filename, "w");
    if (!file) {
        file.close();
        return false;
    }

    // Serialize JSON to file
    if (!serializeConfig(file)) {
        file.close();
        return false;
    }
    file.close();
    return true;
}

bool deserializeConfig(Stream &src)
{
    // Deserialize configuration
    DynamicJsonDocument doc(capacityDeserial);

    // Parse the JSON object in the file
    DeserializationError err = deserializeJson(doc, src);

    if (err) {
        config.load(doc.as<JsonObject>());
        return true;
    } else {
        config.load(doc.as<JsonObject>());
        return true;
    }
    // TODO:  Can I return false here somehow?
}

bool serializeConfig(Print &dst)
{
    // Serialize configuration
    DynamicJsonDocument doc(capacitySerial);

    // Create an object at the root
    JsonObject root = doc.to<JsonObject>();

    // Fill the object
    config.save(root);

    // Serialize JSON to file
    return serializeJsonPretty(doc, dst) > 0;
}

bool printFile()
{
    // Prints the content of a file to the Serial
    File file = SPIFFS.open(filename, "r");
    if (!file)
        return false;

    while (file.available())
        Serial.print((char)file.read());

    Serial.println();
    file.close();
    return true;
}

bool printConfig()
{
    // Serialize configuration
    DynamicJsonDocument doc(capacitySerial);

    // Create an object at the root
    JsonObject root = doc.to<JsonObject>();

    // Fill the object
    config.save(root);

    // Serialize JSON to file
    bool retval = serializeJsonPretty(doc, Serial) > 0;
    Serial.println();
    return retval;
}

bool mergeJsonString(String newJson)
{
    // Serialize configuration
    DynamicJsonDocument doc(capacityDeserial);

    // Parse directly from file
    DeserializationError err = deserializeJson(doc, newJson);
    if (err)
        Serial.println(err.c_str());

    return mergeJsonObject(doc);
}

bool mergeJsonObject(JsonVariantConst src)
{
    // Serialize configuration
    DynamicJsonDocument doc(capacityDeserial);

    // Create an object at the root
    JsonObject root = doc.to<JsonObject>();

    // Fill the object
    config.save(root);

    // Merge in the configuration
    if (merge(root, src))
    {
        // Move new object to config
        config.load(root);
        saveFile();
        return true;
    }

    return false;
}

bool merge(JsonVariant dst, JsonVariantConst src)
{
    if (src.is<JsonObject>())
    {
        for (auto kvp : src.as<JsonObject>())
        {
            merge(dst.getOrAddMember(kvp.key()), kvp.value());
        }
    }
    else
    {
        dst.set(src);
    }
    return true;
}

void ApConfig::save(JsonObject obj) const
{
    obj["ssid"] = ssid;
    obj["passphrase"] = passphrase;
}

void ApConfig::load(JsonObjectConst obj)
{
    // Load Access Point configuration
    //
    if (obj["ssid"].isNull()) {
        strlcpy(ssid, APNAME, sizeof(ssid));
    } else {
        const char* sd = obj["ssid"];
        strlcpy(ssid, sd, sizeof(ssid));
    }

    if (obj["passphrase"].isNull()) {
        strlcpy(passphrase, AP_PASSWD, sizeof(passphrase));
    } else {
        const char* ps = obj["passphrase"];
        strlcpy(passphrase, ps, sizeof(passphrase));
    }

}

void CopConfig::save(JsonObject obj) const
{
    obj["breweryname"] = breweryname;
    obj["kegeratorname"] = kegeratorname;
    obj["imperial"] = imperial;
    obj["numtap"] = numtap;
    obj["rpintscompat"] = rpintscompat;
}

void CopConfig::load(JsonObjectConst obj)
{
    // Load Cop configuration
    //
    if (obj["breweryname"].isNull()) {
        strlcpy(breweryname, BRWYNAME, sizeof(breweryname));
    } else {
        const char* bn = obj["breweryname"];
        strlcpy(breweryname, bn, sizeof(breweryname));
    }

    if (obj["kegeratorname"].isNull()) {
        strlcpy(kegeratorname, KNAME, sizeof(kegeratorname));
    } else {
        const char* kn = obj["kegeratorname"];
        strlcpy(kegeratorname, kn, sizeof(kegeratorname));
    }

    if (obj["imperial"].isNull()) {
        imperial = IMPERIAL;
    } else {
        bool units = obj["imperial"];
        imperial = units;
    }

    if (obj["numtap"].isNull()) {
        numtap = NUMTAPS;
    } else {
        int nt = obj["numtap"];
        numtap = nt;
    }

    if (obj["rpintscompat"].isNull()) {
        rpintscompat = RPINTS;
    } else {
        bool rpints = obj["rpintscompat"];
        rpintscompat = rpints;
    }
}

void Temperatures::save(JsonObject obj) const
{
    obj["setpoint"] = setpoint;
    obj["controlpoint"] = controlpoint;
    obj["roomcal"] = calibration[0];
    obj["towercal"] = calibration[1];
    obj["uppercal"] = calibration[2];
    obj["lowercal"] = calibration[3];
    obj["kegcal"] = calibration[4];
}

void Temperatures::load(JsonObjectConst obj)
{
    // Load Temperature configuration
    //
    if (obj["setpoint"].isNull()) {
        setpoint = DEFSET;
    } else {
        float sp = obj["setpoint"];
        setpoint = sp;
    }

    if (obj["controlpoint"].isNull()) {
        controlpoint = DEFCON;
    } else {
        int cp = obj["controlpoint"];
        controlpoint = cp;
    }

    if (obj["roomcal"].isNull()) {
        calibration[0] = 0.0;
    } else {
        float rc = obj["roomcal"];
        calibration[0] = rc;
    }

    if (obj["towercal"].isNull()) {
        calibration[1] = 0.0;
    } else {
        float tc = obj["towercal"];
        calibration[1] = tc;
    }

    if (obj["uppercal"].isNull()) {
        calibration[2] = 0.0;
    } else {
        float uc = obj["uppercal"];
        calibration[2] = uc;
    }

    if (obj["lowercal"].isNull()) {
        calibration[3] = 0.0;
    } else {
        float lc = obj["lowercal"];
        calibration[3] = lc;
    }

    if (obj["kegcal"].isNull()) {
        calibration[4] = 0.0;
    } else {
        float kc = obj["kegcal"];
        calibration[4] = kc;
    }
}

void URLTarget::save(JsonObject obj) const
{
    obj["url"] = url;
    obj["freq"] = freq;
    obj["update"] = update;
}

void URLTarget::load(JsonObjectConst obj)
{
    // Load URL Target configuration
    //
    if (obj["url"].isNull()) {
        strlcpy(url, "", sizeof(url));
    } else {
        const char* tu = obj["url"];
        strlcpy(url, tu, sizeof(url));
    }

    if (obj["freq"].isNull()) {
        freq = 2;
    } else {
        int f = obj["freq"];
        freq = f;
    }

    if (obj["update"].isNull()) {
        update = false;
    } else {
        bool u = obj["update"];
        update = u;
    }
}

void CloudTarget::save(JsonObject obj) const
{
    obj["type"] = type;
    obj["url"] = url;
    obj["key"] = key;
    obj["freq"] = freq;
    obj["update"] = update;
}

void CloudTarget::load(JsonObjectConst obj)
{
    // Load Cloud configuration
    //
    if (obj["type"].isNull()) {
        strlcpy(key, "", sizeof(type));
    } else {
        const char* t = obj["type"];
        strlcpy(type, t, sizeof(type));
    }

    if (obj["url"].isNull()) {
        strlcpy(url, "", sizeof(url));
    } else {
        const char* u = obj["url"];
        strlcpy(url, u, sizeof(url));
    }

    if (obj["key"].isNull()) {
        strlcpy(key, "", sizeof(key));
    } else {
        const char* k = obj["key"];
        strlcpy(key, k, sizeof(key));
    }

    if (obj["freq"].isNull()) {
        freq = 15;
    } else {
        int f = obj["freq"];
        freq = f;
    }

    if (obj["update"].isNull()) {
        update = false;
    } else {
        bool u = obj["update"];
        update = u;
    }
}

void Config::save(JsonObject obj) const
{
    // Add Access Point object
    apconfig.save(obj.createNestedObject("apconfig"));
    // Add Hostname object
    obj["hostname"] = hostname;
    // Add Bubble object
    copconfig.save(obj.createNestedObject("copconfig"));
    // Add Calibration object
    temps.save(obj.createNestedObject("temps"));
    // Add Target object
    urltarget.save(obj.createNestedObject("urltarget"));
    // Add Cloud object
    cloud.save(obj.createNestedObject("cloud"));
    // Add dospiffs1 object
    obj["dospiffs1"] = dospiffs1;
    // Add dospiffs2 object
    obj["dospiffs2"] = dospiffs2;
    // Add dospiffs1 object
    obj["didupdate"] = didupdate;
}

void Config::load(JsonObjectConst obj)
{
    // Load all config objects
    //

    apconfig.load(obj["apconfig"]);

    if (obj["hostname"].isNull()) {
        strlcpy(hostname, APNAME, sizeof(hostname));
    } else {
        const char* hn = obj["hostname"];
        strlcpy(hostname, hn, sizeof(hostname));
    }

    copconfig.load(obj["copconfig"]);
    temps.load(obj["temps"]);
    urltarget.load(obj["urltarget"]);
    cloud.load(obj["cloud"]);

    if (obj["dospiffs1"].isNull()) {
        dospiffs1 = false;
    } else {
        dospiffs1 = obj["dospiffs1"];
    }

    if (obj["dospiffs2"].isNull()) {
        dospiffs2 = false;
    } else {
        dospiffs2 = obj["dospiffs2"];
    }

    bool firstrun = obj["didupdate"].isNull();
    if (firstrun) {
        didupdate = false;
    } else {
        didupdate = obj["didupdate"];
    }
}
