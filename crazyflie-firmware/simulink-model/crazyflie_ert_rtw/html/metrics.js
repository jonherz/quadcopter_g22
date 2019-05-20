function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.var["rtDW"] = {file: "/Users/Jonas/Documents/Master/Model-based Development/Bitcraze Shared Folder/quadcopter_g22/crazyflie-firmware/simulink-model/crazyflie_ert_rtw/crazyflie.c",
	size: 32};
	 this.metricsArray.var["rtU"] = {file: "/Users/Jonas/Documents/Master/Model-based Development/Bitcraze Shared Folder/quadcopter_g22/crazyflie-firmware/simulink-model/crazyflie_ert_rtw/crazyflie.c",
	size: 80};
	 this.metricsArray.var["rtY"] = {file: "/Users/Jonas/Documents/Master/Model-based Development/Bitcraze Shared Folder/quadcopter_g22/crazyflie-firmware/simulink-model/crazyflie_ert_rtw/crazyflie.c",
	size: 56};
	 this.metricsArray.fcn["atan2"] = {file: "/Applications/MATLAB_R2018b.app/sys/lcc/include/math.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["crazyflie_initialize"] = {file: "/Users/Jonas/Documents/Master/Model-based Development/Bitcraze Shared Folder/quadcopter_g22/crazyflie-firmware/simulink-model/crazyflie_ert_rtw/crazyflie.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["crazyflie_step"] = {file: "/Users/Jonas/Documents/Master/Model-based Development/Bitcraze Shared Folder/quadcopter_g22/crazyflie-firmware/simulink-model/crazyflie_ert_rtw/crazyflie.c",
	stack: 104,
	stackTotal: 104};
	 this.metricsArray.fcn["crazyflie_terminate"] = {file: "/Users/Jonas/Documents/Master/Model-based Development/Bitcraze Shared Folder/quadcopter_g22/crazyflie-firmware/simulink-model/crazyflie_ert_rtw/crazyflie.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["sqrt"] = {file: "/Applications/MATLAB_R2018b.app/sys/lcc/include/math.h",
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
	 this.codeMetricsSummary = '<a href="crazyflie_metrics.html">Global Memory: 168(bytes) Maximum Stack: 104(bytes)</a>';
	}
CodeMetrics.instance = new CodeMetrics();
