#pragma once

#include <json.hpp>
#include <fstream>

class Settings {
public:
	static Settings& get_instance() {
		static Settings settigns;
		return settigns;
	}

	template <typename T>
	T get_params(const std::string& classname, const std::string& field) {
		return get_params_or_default(classname, field, T());
	}

	template <typename T>
	T get_params_or_default(const std::string& classname, const std::string& field, T default_value) {
		json::iterator iter = data.begin();
		for (; iter != data.end(); iter++) {
			if ((*iter).contains("name") && (*iter)["name"].get<std::string>() == classname) {
				break;
			}
		}
		if (iter != data.end() && (*iter).contains(field)) {
			return (*iter)[field].get<T>();
		} else {
			return default_value;
		}
	}
private:
	using json = nlohmann::json;
	json data;
	Settings() {
		std::ifstream ifs("settings.json");
		if (ifs.is_open()) {
			ifs >> data;
			ifs.close();
		}
	}
};