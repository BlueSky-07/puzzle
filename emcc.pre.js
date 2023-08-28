Module.preRun=[function() {
  ENV.LOGGER = "true";
  ENV.LOGGER_LEVEL = "verbose";
  if (ENVIRONMENT_IS_WEB) arguments_.push("0");
}]
