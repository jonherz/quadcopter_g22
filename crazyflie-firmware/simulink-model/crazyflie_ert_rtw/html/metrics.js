function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.var["rtDW"] = {file: "C:\\Users\\gusta\\Desktop\\Bitcraze Shared Folder\\quadcopter_g22\\crazyflie-firmware\\simulink-model\\crazyflie_ert_rtw\\crazyflie.c",
	size: 16};
	 this.metricsArray.var["rtU"] = {file: "C:\\Users\\gusta\\Desktop\\Bitcraze Shared Folder\\quadcopter_g22\\crazyflie-firmware\\simulink-model\\crazyflie_ert_rtw\\crazyflie.c",
	size: 80};
	 this.metricsArray.var["rtY"] = {file: "C:\\Users\\gusta\\Desktop\\Bitcraze Shared Folder\\quadcopter_g22\\crazyflie-firmware\\simulink-model\\crazyflie_ert_rtw\\crazyflie.c",
	size: 56};
	 this.metricsArray.fcn["atan2"] = {file: "C:\\Program Files\\MATLAB\\R2018b\\sys\\lcc\\include\\math.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["crazyflie_initialize"] = {file: "C:\\Users\\gusta\\Desktop\\Bitcraze Shared Folder\\quadcopter_g22\\crazyflie-firmware\\simulink-model\\crazyflie_ert_rtw\\crazyflie.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["crazyflie_step"] = {file: "C:\\Users\\gusta\\Desktop\\Bitcraze Shared Folder\\quadcopter_g22\\crazyflie-firmware\\simulink-model\\crazyflie_ert_rtw\\crazyflie.c",
	stack: 40,
	stackTotal: 40};
	 this.metricsArray.fcn["crazyflie_terminate"] = {file: "C:\\Users\\gusta\\Desktop\\Bitcraze Shared Folder\\quadcopter_g22\\crazyflie-firmware\\simulink-model\\crazyflie_ert_rtw\\crazyflie.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["sqrt"] = {file: "C:\\Program Files\\MATLAB\\R2018b\\sys\\lcc\\include\\math.h",
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
	 this.codeMetricsSummary = '<a href="crazyflie_metrics.html">Global Memory: 152(bytes) Maximum Stack: 40(bytes)</a>';
	}
CodeMetrics.instance = new CodeMetrics();
