#include <depthai/build/version.hpp>
#include <depthai/depthai.hpp>
#include <iostream>

void get_info(const dai::TensorInfo &tensor) {

  std::map<int, std::string> storage_order = {
      {0x4213, "NHWC"}, {0x4231, "NHCW"}, {0x4321, "NCHW"}, {0x213, "HWC"},
      {0x321, "CHW"},   {0x123, "WHC"},   {0x231, "HCW"},   {0x132, "WCH"},
      {0x312, "CWH"},   {0x43, "NC"},     {0x34, "CN"},     {0x3, "C"},
      {0x2, "H"},       {0x1, "W"},
  };

  std::string data_type[5] = {
      "FP16", // Half precision floating point
      "U8F",  // Unsigned byte
      "INT",  // Signed integer (4 byte)
      "FP32", // Single precision floating point
      "I8",   // Signed byte
  };

  nlohmann::json json = tensor;
  json["dataType"] = data_type[int(tensor.dataType)];
  std::vector<unsigned> dims;
  std::for_each(tensor.dims.rbegin(), tensor.dims.rend(),
                [&](const auto &item) { dims.push_back(item); });
  json["dims"] = dims;

  json["order"] = storage_order[static_cast<int>(tensor.order)];

  std::cout << json.dump(2) << std::endl;
}

int main(int argc, char *argv[]) {
  std::cout << "Depthai Version: " << dai::build::VERSION << " "
            << dai::build::COMMIT << std::endl;
  auto BLOB_PATH = getenv("BLOB_PATH");
  if (argc != 2) {
    if (BLOB_PATH == nullptr) {
      std::cerr << "\033[31m"
                << "Error: "
                << "A parameter (BLOB_PATH) is required or the BLOB_PATH "
                   "environment variable exists !"
                << "\033[0m" << std::endl;
      return EXIT_FAILURE;
    }
  } else {
    BLOB_PATH = argv[1];
  }
  dai::OpenVINO::Blob net(BLOB_PATH);

  std::cout << "Blob OpenVINO Version: "
            << dai::OpenVINO::getVersionName(net.version) << std::endl;

  std::unordered_map<std::string, dai::TensorInfo> networkInputs =
      net.networkInputs;

  for (auto &networkInput : networkInputs) {
    std::cout << "NetworkInputs: \n  " << networkInput.first << ":"
              << std::endl;
    get_info(networkInput.second);
  }

  std::unordered_map<std::string, dai::TensorInfo> networkOutputs =
      net.networkOutputs;
  for (auto &networkOutput : networkOutputs) {
    std::cout << "NetworkOutputs: \n  " << networkOutput.first << ":"
              << std::endl;
    get_info(networkOutput.second);
  }

  return 0;
}
