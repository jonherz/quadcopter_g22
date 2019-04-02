function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.var["rtU"] = {file: "/Users/Jonas/Documents/Master/Model-based Development/Bitcraze Shared Folder/quadcopter_g22/crazyflie-firmware/simulink-model/crazyflie_ert_rtw/crazyflie.c",
	size: 80};
	 this.metricsArray.var["rtY"] = {file: "/Users/Jonas/Documents/Master/Model-based Development/Bitcraze Shared Folder/quadcopter_g22/crazyflie-firmware/simulink-model/crazyflie_ert_rtw/crazyflie.c",
	size: 56};
	 this.metricsArray.fcn["crazyflie_initialize"] = {file: "/Users/Jonas/Documents/Master/Model-based Development/Bitcraze Shared Folder/quadcopter_g22/crazyflie-firmware/simulink-model/crazyflie_ert_rtw/crazyflie.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["crazyflie_step"] = {file: "/Users/Jonas/Documents/Master/Model-based Development/Bitcraze Shared Folder/quadcopter_g22/crazyflie-firmware/simulink-model/crazyflie_ert_rtw/crazyflie.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["crazyflie_terminate"] = {file: "/Users/Jonas/Documents/Master/Model-based Development/Bitcraze Shared Folder/quadcopter_g22/crazyflie-firmware/simulink-model/crazyflie_ert_rtw/crazyflie.c",
	stack: 0,
	stackTotal: 0};
	 this.getMetrics = function(token) { 
		 var data;
		 data = this.metricsArray.var[token];
		 if (!data) {
			 data = this.metricsArray.fcn[token];
			 if (data) data.type = "fcn";
		 } else { 
			 data.type = "var";
		 }
	 return data; }; 
	 this.codeMetricsSummary = '<a href="crazyflie_metrics.html">Global Memory: 136(bytes) Maximum Stack: 0(bytes)</a>';
	}
CodeMetrics.instance = new CodeMetrics();
