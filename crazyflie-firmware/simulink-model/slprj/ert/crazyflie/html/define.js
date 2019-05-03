function CodeDefine() { 
this.def = new Array();
this.def["crazyflie"] = {file: "crazyflie_c.html",line:31,type:"fcn"};this.def["crazyflie_DW_f"] = {file: "crazyflie_h.html",line:39,type:"type"};this.def["crazyflie_MdlrefDW"] = {file: "crazyflie_h.html",line:43,type:"type"};this.def["rtCP_pooled_1Qdtb1yqs7Tg"] = {file: "../../_sharedutils/html/const_params_c.html",line:17,type:"var"};this.def["rtCP_pooled_VoPnT3ZVOFV2"] = {file: "../../_sharedutils/html/const_params_c.html",line:30,type:"var"};this.def["rtCP_pooled_jcy6zylU07za"] = {file: "../../_sharedutils/html/const_params_c.html",line:43,type:"var"};this.def["int8_T"] = {file: "../../_sharedutils/html/rtwtypes_h.html",line:46,type:"type"};this.def["uint8_T"] = {file: "../../_sharedutils/html/rtwtypes_h.html",line:47,type:"type"};this.def["int16_T"] = {file: "../../_sharedutils/html/rtwtypes_h.html",line:48,type:"type"};this.def["uint16_T"] = {file: "../../_sharedutils/html/rtwtypes_h.html",line:49,type:"type"};this.def["int32_T"] = {file: "../../_sharedutils/html/rtwtypes_h.html",line:50,type:"type"};this.def["uint32_T"] = {file: "../../_sharedutils/html/rtwtypes_h.html",line:51,type:"type"};this.def["real32_T"] = {file: "../../_sharedutils/html/rtwtypes_h.html",line:52,type:"type"};this.def["real64_T"] = {file: "../../_sharedutils/html/rtwtypes_h.html",line:53,type:"type"};this.def["real_T"] = {file: "../../_sharedutils/html/rtwtypes_h.html",line:59,type:"type"};this.def["time_T"] = {file: "../../_sharedutils/html/rtwtypes_h.html",line:60,type:"type"};this.def["boolean_T"] = {file: "../../_sharedutils/html/rtwtypes_h.html",line:61,type:"type"};this.def["int_T"] = {file: "../../_sharedutils/html/rtwtypes_h.html",line:62,type:"type"};this.def["uint_T"] = {file: "../../_sharedutils/html/rtwtypes_h.html",line:63,type:"type"};this.def["ulong_T"] = {file: "../../_sharedutils/html/rtwtypes_h.html",line:64,type:"type"};this.def["char_T"] = {file: "../../_sharedutils/html/rtwtypes_h.html",line:65,type:"type"};this.def["uchar_T"] = {file: "../../_sharedutils/html/rtwtypes_h.html",line:66,type:"type"};this.def["byte_T"] = {file: "../../_sharedutils/html/rtwtypes_h.html",line:67,type:"type"};this.def["pointer_T"] = {file: "../../_sharedutils/html/rtwtypes_h.html",line:85,type:"type"};this.def["isInit"] = {file: "crazyflieModel_c.html",line:35,type:"var"};this.def["sensorData"] = {file: "crazyflieModel_c.html",line:36,type:"var"};this.def["setpoint"] = {file: "crazyflieModel_c.html",line:37,type:"var"};this.def["state"] = {file: "crazyflieModel_c.html",line:38,type:"var"};this.def["l6"] = {file: "crazyflieModel_c.html",line:39,type:"var"};this.def["m4"] = {file: "crazyflieModel_c.html",line:40,type:"var"};this.def["crazyflieModelInit"] = {file: "crazyflieModel_c.html",line:41,type:"fcn"};this.def["crazyflieModelTest"] = {file: "crazyflieModel_c.html",line:62,type:"fcn"};this.def["crazyflieModelTask"] = {file: "crazyflieModel_c.html",line:70,type:"fcn"};}
CodeDefine.instance = new CodeDefine();
var testHarnessInfo = {OwnerFileName: "", HarnessOwner: "", HarnessName: "", IsTestHarness: "0"};
var relPathToBuildDir = "../ert_main.c";
var fileSep = "/";
var isPC = false;
function Html2SrcLink() {
	this.html2SrcPath = new Array;
	this.html2Root = new Array;
	this.html2SrcPath["crazyflie_c.html"] = "../crazyflie.c";
	this.html2Root["crazyflie_c.html"] = "crazyflie_c.html";
	this.html2SrcPath["crazyflie_h.html"] = "../crazyflie.h";
	this.html2Root["crazyflie_h.html"] = "crazyflie_h.html";
	this.html2SrcPath["const_params_c.html"] = "../const_params.c";
	this.html2Root["const_params_c.html"] = "../../_sharedutils/html/const_params_c.html";
	this.html2SrcPath["rtwtypes_h.html"] = "../rtwtypes.h";
	this.html2Root["rtwtypes_h.html"] = "../../_sharedutils/html/rtwtypes_h.html";
	this.html2SrcPath["crazyflieModel_c.html"] = "../crazyflieModel.c";
	this.html2Root["crazyflieModel_c.html"] = "crazyflieModel_c.html";
	this.html2SrcPath["crazyflieModel_h.html"] = "../crazyflieModel.h";
	this.html2Root["crazyflieModel_h.html"] = "crazyflieModel_h.html";
	this.getLink2Src = function (htmlFileName) {
		 if (this.html2SrcPath[htmlFileName])
			 return this.html2SrcPath[htmlFileName];
		 else
			 return null;
	}
	this.getLinkFromRoot = function (htmlFileName) {
		 if (this.html2Root[htmlFileName])
			 return this.html2Root[htmlFileName];
		 else
			 return null;
	}
}
Html2SrcLink.instance = new Html2SrcLink();
var fileList = [
"crazyflie_c.html","crazyflie_h.html","const_params_c.html","rtwtypes_h.html","crazyflieModel_c.html","crazyflieModel_h.html"];
