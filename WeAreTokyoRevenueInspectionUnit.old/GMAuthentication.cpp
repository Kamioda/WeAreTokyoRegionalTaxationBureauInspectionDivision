#include "Ini.h"
#include "GetEnvironmentVariable.h"
#include "GetUser.h"
#include <Shlwapi.h>

struct GMInfo {
	struct MachineInfo {
		MachineInfo(const std::string computername, const std::string username, const std::string fullname)
			: computername(computername), username(username), fullname(fullname) {}
		std::string computername;
		std::string username;
		std::string fullname;
		bool operator == (const MachineInfo m) {
			return this->computername == m.computername && this->username == m.username && this->fullname == m.fullname;
		}
	};
	GMInfo(const int ID, const std::string pw, MachineInfo machine) : ID(ID), pw(pw), machine(machine) {}
	int ID;
	std::string pw;
	MachineInfo machine;
	bool operator == (const GMInfo g) { return this->ID == g.ID && this->pw == g.pw && this->machine == g.machine; }
};

const GMInfo gamemaster_list[4] = {
	GMInfo(0, "kagucho2503", GMInfo::MachineInfo("KAMIMEGU-VAIO", "Kamioda", "神御田" )),
	GMInfo(1, "happinesschargeprecure2014", GMInfo::MachineInfo("KAMIMEGU-VAIO", "AinoMegumi", "あいめぐ")),
	GMInfo(2, "yumeiro2014", GMInfo::MachineInfo("AMAKAMI-VAIO", "AmanoIchigo", "AmanoIchigo")),
	GMInfo(3, "kaguchokamioda20140401", GMInfo::MachineInfo("AMAKAMI-VAIO", "聖人", "神御田聖人"))
};

static inline int get_gm_id(Ini ini) {
	return ini.getnum("GameMaster", "ID", 0);
}

bool is_game_master_mode(const std::string& command_line) {
	if (command_line != "/mode:gm") return false;
	EnvironmentVariable env = EnvironmentVariable();
	const std::string gminfo_filepath = env.get_variable_num("AppData") + "\\Kamioda Games\\wtriugm.ini";
	if (FALSE == PathFileExistsA(gminfo_filepath.c_str())) return false;
	Ini ini(gminfo_filepath);
	return GMInfo(
		get_gm_id(ini),
		ini.getString("GameMaster", "pw", ""),
		GMInfo::MachineInfo(
			env.get_variable_num("ComputerName"),
			env.get_variable_num("UserName"),
			GetUser().search_user_name_to_full_name(env.get_variable_num("UserName"))
		)
	) == gamemaster_list[get_gm_id(ini)];
}
