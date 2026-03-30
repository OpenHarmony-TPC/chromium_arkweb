import os
import json
import datetime


weekday_index = datetime.datetime.today().weekday()
version_number = os.getenv("version_Number")
sp_version_raw = os.getenv("sp_Version")
json_path = "./src/third_party/ohos_nweb_hap/AppScope/app.json5.template"
with open(json_path, "r", encoding="utf-8") as f:
    data = json.load(f)
original_code = str(data["app"].get("versionCode"))
original_name = data["app"].get("versionName")
base_prefix = original_code[:4]
base_version = original_code[4:7]
base_spcode = original_code[7:9]
if "sp" in original_name:
    base_name_version = original_name.split(".")[-1].split("sp")[0]
    base_name_sp = original_name.split("sp")[-1]
else:
    base_name_version = original_name.split(".")[-1]
    base_name_sp = ""
new_version_code_str = base_version
new_version_name_str = base_name_version
new_spcode_str = base_spcode
new_sp_label = f"sp{base_name_sp}"
try:
    if version_number and version_number.isdigit():
        version_number_raw = version_number
        if len(version_number) == 2:
            new_version_code_str = "0" + version_number
        elif len(version_number) == 3:
            new_version_code_str = version_number
        else:
            raise ValueError("version_Number error")
        new_version_name_str = version_number_raw
    if sp_version_raw:
        sp_values = sp_version_raw.strip().split(",")
        if len(sp_values) != 7:
            raise ValueError(f"sp_version_raw length error: expected 7, got {len(sp_values)}")
        if not sp_values[weekday_index].isdigit():
            raise ValueError(f"sp_version_raw value at index {weekday_index} is not a digit: {sp_values[weekday_index]}")
        sp_today = int(sp_values[weekday_index])
        new_spcode_str = f"{sp_today:02d}"
        new_sp_label = f"sp{sp_today}"
        should_update = True
    if version_number or sp_version_raw:
        updated_code = f"{base_prefix}{new_version_code_str}{new_spcode_str}"
        dot_index = original_name.rfind(".")
        prefix_name = original_name[:dot_index]
        if new_spcode_str == "00":
            updated_name = f"{prefix_name}.{new_version_name_str}"
        else:
            updated_name = f"{prefix_name}.{new_version_name_str}{new_sp_label}"
        data["app"]["versionCode"] = int(updated_code)
        data["app"]["versionName"] = updated_name
        with open(json_path, "w", encoding="utf-8") as f:
            json.dump(data, f, indent=2, ensure_ascii=False)
        print(f"versionCode → {updated_code}")
        print(f"versionName → {updated_name}")
    else:
        print("versionCode and versionName not change")
except ValueError as e:
    print(f"Error: {e}")
