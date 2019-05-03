function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.fcn["atan2"] = {file: "/Applications/MATLAB_R2018b.app/sys/lcc/include/math.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["crazyflie"] = {file: "/Users/Jonas/Documents/Master/Model-based Development/Bitcraze Shared Folder/quadcopter_g22/crazyflie-firmware/simulink-model/slprj/ert/crazyflie/crazyflie.c",
	stack: 152,
	stackTotal: 152};
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
	 this.codeMetricsSummary = '<a href="crazyflie_metrics.html">Global Memory: 0(bytes) Maximum Stack: 152(bytes)</a>';
	}
CodeMetrics.instance = new CodeMetrics();
