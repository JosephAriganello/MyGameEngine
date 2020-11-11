#include "Debug.h"

MessageType Debug::currentSeverity = MessageType::TYPE_NONE;

void Debug::DebugInit() {

	//This will create the file what the debugger will be writing to.
	std::ofstream out;
	out.open("GAME301Log.txt", std::ios::out);
	out.close();

	//By default, the error severity is fatal.
	currentSeverity = MessageType::TYPE_FATAL_ERROR;
}

void Debug::SetSeverity(MessageType type_) {
	currentSeverity = type_;
}

//This is for general logging.
void Debug::Log(const MessageType type_, const std::string& message_, const std::string& filename_, const int line_) {
	if (type_ <= currentSeverity && currentSeverity > MessageType::TYPE_NONE) {
		std::ofstream file;
		file.open("GAME301Log.txt", std::ios::out);
		file << message_ << " in file: " << filename_ << " on line: " << line_ << std::endl;
		file.flush();
		file.close();
	}
}

//This is for info logging.
void Debug::Info(const std::string& message_, const std::string& filename_, const int line_) {
	Log(MessageType::TYPE_INFO, "[INFO]: " + message_, filename_, line_);
}

//This is for trace logging.
void Debug::Trace(const std::string& message_, const std::string& filename_, const int line_) {
	Log(MessageType::TYPE_TRACE, "[TRACE]: " + message_, filename_, line_);
}

//This is for warning logging (automatic-ish).
void Debug::Warning(const std::string& message_, const std::string& filename_, const int line_) {
	Log(MessageType::TYPE_WARNING, "[WARNING]: " + message_, filename_, line_);
}

//This is for error logging (automatic-ish).
void Debug::Error(const std::string& message_, const std::string& filename_, const int line_) {
	Log(MessageType::TYPE_ERROR, "[ERROR]: " + message_, filename_, line_);
}

//This is for fatal error logging (automatic-ish).
void Debug::FatalError(const std::string& message_, const std::string& filename_, const int line_) {
	Log(MessageType::TYPE_FATAL_ERROR, "[FATAL ERROR]: " + message_, filename_, line_);
}

