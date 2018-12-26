#include "lib.h"

#include <iostream>

#include <spdlog/spdlog.h>

int main() {
	auto const logger{spdlog::stdout_logger_mt("console")};

	if (logger) {
		logger->info("version {} was started", version());
	}

	return 0;
}
