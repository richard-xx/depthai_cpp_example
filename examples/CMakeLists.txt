if (USE_NETWORK_SOURCE)
    # NeuralNetwork node, mobilenet example
    hunter_private_data(
            URL "https://artifacts.luxonis.com/artifactory/luxonis-depthai-data-local/network/mobilenet-ssd_openvino_2021.4_6shave.blob"
            SHA1 "4f4506726e3083981064938a0faaf9af6180d2c6"
            FILE "mobilenet-ssd_openvino_2021.4_6shave.blob"
            LOCATION mobilenet_blob
    )

    # YoloV3 资源
    hunter_private_data(
            URL "http://artifacts.luxonis.com/artifactory/luxonis-depthai-data-local/network/yolo-v3-tiny-tf_openvino_2021.4_6shave.blob"
            SHA1 "dedb2d4d96b23e42d15c15e454b8f02eca2713de"
            FILE "yolo-v3-tiny-tf_openvino_2021.4_6shave.blob"
            LOCATION tiny_yolo_v3_blob
    )

    # YoloV4 资源
    hunter_private_data(
            URL "https://artifacts.luxonis.com/artifactory/luxonis-depthai-data-local/network/yolo-v4-tiny-tf_openvino_2021.4_6shave.blob"
            SHA1 "d8d09b697dac298fe83cf8856740a21b1a61ab89"
            FILE "yolo-v4-tiny-tf_openvino_2021.4_6shave.blob"
            LOCATION tiny_yolo_v4_blob
    )

    # NeuralNetwork node, mobilenet example, 5 shaves
    hunter_private_data(
            URL "https://artifacts.luxonis.com/artifactory/luxonis-depthai-data-local/network/mobilenet-ssd_openvino_2021.4_5shave.blob"
            SHA1 "14ab3ef446b8a649d6694d94c2fc8b798efd74a3"
            FILE "mobilenet-ssd_openvino_2021.4_5shave.blob"
            LOCATION mobilenet_5shaves_blob
    )

    # NeuralNetwork node, mobilenet example, 8 shaves
    hunter_private_data(
            URL "https://artifacts.luxonis.com/artifactory/luxonis-depthai-data-local/network/mobilenet-ssd_openvino_2021.4_8shave.blob"
            SHA1 "7e7ea9a680668f3ca9e8f1d22cc8f3f1a02ac018"
            FILE "mobilenet-ssd_openvino_2021.4_8shave.blob"
            LOCATION mobilenet_8shaves_blob
    )

    # 带有要检测的对象的视频文件
    hunter_private_data(
            URL "https://artifacts.luxonis.com/artifactory/luxonis-depthai-data-local/network/construction_vest.mp4"
            SHA1 "271d8d0b702e683ce02957db7c100843de5ceaec"
            FILE "construction_vest.mp4"
            LOCATION construction_vest
    )

    # Calibration Sample files
    hunter_private_data(
            URL "https://artifacts.luxonis.com/artifactory/luxonis-depthai-data-local/misc/depthai_calib.json"
            SHA1 "ec50a47496473116c51cec1c8249bff2679383c3"
            FILE "depthai_calib.json"
            LOCATION calib_v6
    )

    hunter_private_data(
            URL "https://artifacts.luxonis.com/artifactory/luxonis-depthai-data-local/misc/depthai_v5.calib"
            SHA1 "adfe9976b9aacfdaa76ac7138810999988177e71"
            FILE "depthai_v5.calib"
            LOCATION calib_v5
    )

    hunter_private_data(
            URL "https://artifacts.luxonis.com/artifactory/luxonis-depthai-data-local/misc/BW1098OBC.json"
            SHA1 "1e84b6c339ac51e3b254775090b91235a40fac71"
            FILE "BW1098OBC.json"
            LOCATION device_config
    )

    # person-detection
    hunter_private_data(
            URL "https://artifacts.luxonis.com/artifactory/luxonis-depthai-data-local/network/person-detection-retail-0013_openvino_2021.4_7shave.blob"
            SHA1 "946d102874b287292cdb5952fa66356c8d36025f"
            FILE "person-detection-retail-0013_openvino_2021.4_7shave.blob"
            LOCATION person_detection
    )

    # concat model
    hunter_private_data(
            URL "https://artifacts.luxonis.com/artifactory/luxonis-depthai-data-local/network/concat_openvino_2021.4_6shave.blob"
            SHA1 "e4af6fb2bed39648a2a4424d8bdc5bac56d616df"
            FILE "concat_openvino_2021.4_6shave.blob"
            LOCATION concat_model
    )

    # normalization model
    hunter_private_data(
            URL "https://artifacts.luxonis.com/artifactory/luxonis-depthai-data-local/network/normalize_openvino_2021.4_4shave.blob"
            SHA1 "1435f6d11e0dfdbc60f2dfa45aecd3d530b6153b"
            FILE "normalize_openvino_2021.4_4shave.blob"
            LOCATION normalization_model
    )
else ()
    if (NOT EXISTS models)
        message(FATAL_ERROR "No resource exist, Please download https://github.com/richard-xx/depthai_cpp_example/releases/download/v2.16.0/models.zip and extract it to the examples directory, or set USE_NETWORK_SOURCE to ON" )
    endif ()
    set(mobilenet_blob "models/mobilenet-ssd_openvino_2021.4_6shave.blob")
    set(tiny_yolo_v3_blob "models/yolo-v3-tiny-tf_openvino_2021.4_6shave.blob")
    set(tiny_yolo_v4_blob "models/yolo-v4-tiny-tf_openvino_2021.4_6shave.blob")
    set(mobilenet_5shaves_blob "models/mobilenet-ssd_openvino_2021.4_5shave.blob")
    set(mobilenet_8shaves_blob "models/mobilenet-ssd_openvino_2021.4_8shave.blob")
    set(construction_vest "models/construction_vest.mp4")
    set(calib_v6 "models/depthai_calib.json")
    set(calib_v5 "models/depthai_v5.calib")
    set(device_config "models/BW1098OBC.json")
    set(person_detection "models/person-detection-retail-0013_openvino_2021.4_7shave.blob")
    set(concat_model "models/concat_openvino_2021.4_6shave.blob")
    set(normalization_model "models/normalize_openvino_2021.4_4shave.blob")
    #    file(GLOB models "models/*")
    file(COPY models DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
    install(DIRECTORY models DESTINATION "${INSTALL_BINDIR}")

endif ()

# bootloader
dai_add_example(bootloader_version bootloader/bootloader_version.cpp)
dai_add_example(flash_bootloader bootloader/flash_bootloader.cpp)
dai_add_example(flash_user_bootloader bootloader/flash_user_bootloader.cpp)
dai_add_example(bootloader_config bootloader/bootloader_config.cpp)
dai_add_example(poe_set_ip bootloader/poe_set_ip.cpp)
dai_add_example(read_flash_memory bootloader/read_flash_memory.cpp)
dai_add_example(write_flash_memory bootloader/write_flash_memory.cpp)
dai_add_example(flash_boot_header bootloader/flash_boot_header.cpp)

# calibration
dai_add_example(calibration_flash calibration/calibration_flash.cpp)
dai_add_example(calibration_flash_version5 calibration/calibration_flash_v5.cpp)
dai_add_example(calibration_load calibration/calibration_load.cpp)
dai_add_example(calibration_reader calibration/calibration_reader.cpp)
dai_add_example(calibration_dump calibration/calibration_dump.cpp)
dai_add_example(calibration_factory_reset calibration/calibration_factory_reset.cpp)

target_compile_definitions(calibration_flash PRIVATE CALIB_PATH="${calib_v6}")
target_compile_definitions(calibration_flash_version5 PRIVATE CALIB_PATH="${calib_v5}" BOARD_PATH="${device_config}")
target_compile_definitions(calibration_load PRIVATE CALIB_PATH="${calib_v6}")

# ColorCamera
dai_add_example(rgb_camera_control ColorCamera/rgb_camera_control.cpp)
dai_add_example(rgb_preview ColorCamera/rgb_preview.cpp)
dai_add_example(rgb_video ColorCamera/rgb_video.cpp)
dai_add_example(rgb_isp_scale ColorCamera/rgb_isp_scale.cpp)

# EdgeDetector
dai_add_example(edge_detector EdgeDetector/edge_detector.cpp)

# FeatureTracker
dai_add_example(feature_detector FeatureTracker/feature_detector.cpp)
dai_add_example(feature_tracker FeatureTracker/feature_tracker.cpp)

# host_side
dai_add_example(device_queue_event host_side/device_queue_event.cpp)
dai_add_example(opencv_support host_side/opencv_support.cpp)
dai_add_example(queue_add_callback host_side/queue_add_callback.cpp)
dai_add_example(device_information host_side/device_information.cpp)
dai_add_example(device_logging host_side/device_logging.cpp)

# ImageManip
dai_add_example(image_manip ImageManip/image_manip_example.cpp)
dai_add_example(image_manip_rotate ImageManip/image_manip_rotate.cpp)
dai_add_example(image_manip_tiling ImageManip/image_manip_tiling.cpp)
dai_add_example(rgb_rotate_warp ImageManip/rgb_rotate_warp.cpp)
dai_add_example(image_manip_warp_mesh ImageManip/image_manip_warp_mesh.cpp)

# Warp
dai_add_example(warp_mesh Warp/warp_mesh.cpp)

# IMU
dai_add_example(imu_gyroscope_accelerometer IMU/imu_gyroscope_accelerometer.cpp)
dai_add_example(imu_rotation_vector IMU/imu_rotation_vector.cpp)
dai_add_example(imu_firmware_update IMU/imu_firmware_update.cpp)

# mixed
dai_add_example(mono_depth_mobilenetssd mixed/mono_depth_mobilenetssd.cpp)
dai_add_example(rgb_encoding_mono_mobilenet mixed/rgb_encoding_mono_mobilenet.cpp)
dai_add_example(rgb_encoding_mono_mobilenet_depth mixed/rgb_encoding_mono_mobilenet_depth.cpp)
dai_add_example(rgb_encoding_mobilenet mixed/rgb_encoding_mobilenet.cpp)
dai_add_example(multiple_devices mixed/multiple_devices.cpp)
dai_add_example(frame_sync mixed/frame_sync.cpp)

target_compile_definitions(mono_depth_mobilenetssd PRIVATE BLOB_PATH="${mobilenet_blob}")
target_compile_definitions(rgb_encoding_mono_mobilenet PRIVATE BLOB_PATH="${mobilenet_blob}")
target_compile_definitions(rgb_encoding_mono_mobilenet_depth PRIVATE BLOB_PATH="${mobilenet_blob}")
target_compile_definitions(rgb_encoding_mobilenet PRIVATE BLOB_PATH="${mobilenet_blob}")

# MobileNet
dai_add_example(camera_mobilenet_sync MobileNet/camera_mobilenet_sync_example.cpp -lpthread -lm)
dai_add_example(rgb_mobilenet MobileNet/rgb_mobilenet.cpp)
dai_add_example(rgb_mobilenet_4k MobileNet/rgb_mobilenet_4k.cpp)
dai_add_example(mono_mobilenet MobileNet/mono_mobilenet.cpp)
dai_add_example(video_mobilenet MobileNet/video_mobilenet.cpp)
# Usually not available - removed from tests
# TODO - add to a separate group if possible
dai_add_example(webcam_mobilenet MobileNet/webcam_mobilenet_example.cpp)

target_compile_definitions(camera_mobilenet_sync PRIVATE BLOB_PATH="${mobilenet_blob}")
target_compile_definitions(rgb_mobilenet PRIVATE BLOB_PATH="${mobilenet_blob}")
target_compile_definitions(rgb_mobilenet_4k PRIVATE BLOB_PATH="${mobilenet_5shaves_blob}")
target_compile_definitions(mono_mobilenet PRIVATE BLOB_PATH="${mobilenet_blob}")
target_compile_definitions(video_mobilenet PRIVATE BLOB_PATH="${mobilenet_8shaves_blob}" VIDEO_PATH="${construction_vest}")
target_compile_definitions(webcam_mobilenet PRIVATE BLOB_PATH="${mobilenet_8shaves_blob}")

# MonoCamera
dai_add_example(mono_camera_control MonoCamera/mono_camera_control.cpp)
dai_add_example(mono_preview MonoCamera/mono_preview.cpp)
dai_add_example(mono_full_resolution_saver MonoCamera/mono_full_resolution_saver.cpp)

# NeuralNetwork
dai_add_example(concatenate NeuralNetwork/concat_multi_input.cpp)
dai_add_example(normalize NeuralNetwork/normalization_multi_input.cpp)

target_compile_definitions(concatenate PRIVATE BLOB_PATH="${concat_model}")
target_compile_definitions(normalize PRIVATE BLOB_PATH="${normalization_model}")

# ObjectTracker
dai_add_example(object_tracker ObjectTracker/object_tracker.cpp)
dai_add_example(spatial_object_tracker ObjectTracker/spatial_object_tracker.cpp)
dai_add_example(object_tracker_video ObjectTracker/object_tracker_video.cpp)

target_compile_definitions(object_tracker PRIVATE BLOB_PATH="${mobilenet_blob}")
target_compile_definitions(spatial_object_tracker PRIVATE BLOB_PATH="${mobilenet_5shaves_blob}")
target_compile_definitions(object_tracker_video PRIVATE BLOB_PATH="${person_detection}" VIDEO_PATH="${construction_vest}")

# Script
dai_add_example(script_camera_control Script/script_camera_control.cpp)
dai_add_example(script_forward_frames Script/script_forward_frames.cpp)
dai_add_example(script_get_ip Script/script_get_ip.cpp)
dai_add_example(script_http_client Script/script_http_client.cpp)
dai_add_example(script_http_server Script/script_http_server.cpp)
dai_add_example(script_mjpeg_server Script/script_mjpeg_server.cpp)
dai_add_example(script_nndata_example Script/script_nndata_example.cpp)
dai_add_example(script_json_communication Script/script_json_communication.cpp)
dai_add_example(script_change_pipeline_flow Script/script_change_pipeline_flow.cpp)
target_compile_definitions(script_change_pipeline_flow PRIVATE BLOB_PATH="${mobilenet_5shaves_blob}")
dai_add_example(script_get_device_info Script/script_get_device_info.cpp)
dai_add_example(script_read_calibration Script/script_read_calibration.cpp)

# SpatialDetection
dai_add_example(spatial_location_calculator SpatialDetection/spatial_location_calculator.cpp)
dai_add_example(spatial_mobilenet_mono SpatialDetection/spatial_mobilenet_mono.cpp)
dai_add_example(spatial_mobilenet SpatialDetection/spatial_mobilenet.cpp)
dai_add_example(spatial_tiny_yolo_v3 SpatialDetection/spatial_tiny_yolo.cpp)
dai_add_example(spatial_tiny_yolo_v4 SpatialDetection/spatial_tiny_yolo.cpp)
dai_add_example(spatial_calculator_multi_roi SpatialDetection/spatial_calculator_multi_roi.cpp)

target_compile_definitions(spatial_mobilenet_mono PRIVATE BLOB_PATH="${mobilenet_blob}")
target_compile_definitions(spatial_mobilenet PRIVATE BLOB_PATH="${mobilenet_blob}")
target_compile_definitions(spatial_tiny_yolo_v3 PRIVATE BLOB_PATH="${tiny_yolo_v3_blob}")
target_compile_definitions(spatial_tiny_yolo_v4 PRIVATE BLOB_PATH="${tiny_yolo_v4_blob}")

# StereoDepth
dai_add_example(depth_crop_control StereoDepth/depth_crop_control.cpp)
dai_add_example(depth_preview StereoDepth/depth_preview.cpp)
dai_add_example(depth_post_processing StereoDepth/depth_post_processing.cpp)
dai_add_example(rgb_depth_aligned StereoDepth/rgb_depth_aligned.cpp)
dai_add_example(rgb_depth_confidence_aligned StereoDepth/rgb_depth_confidence_aligned.cpp)
dai_add_example(stereo_depth_video StereoDepth/stereo_depth_video.cpp)

# SystemLogger
dai_add_example(system_information SystemLogger/system_information.cpp)

# VideoEncoder
dai_add_example(disparity_encoding VideoEncoder/disparity_encoding.cpp)
dai_add_example(rgb_encoding VideoEncoder/rgb_encoding.cpp)
dai_add_example(rgb_full_resolution_saver VideoEncoder/rgb_full_resolution_saver.cpp)
dai_add_example(rgb_mono_encoding VideoEncoder/rgb_mono_encoding.cpp)
dai_add_example(encoding_max_limit VideoEncoder/encoding_max_limit.cpp)
dai_add_example(mjpeg_encoding VideoEncoder/mjpeg_encoding_example.cpp)

# Yolo
dai_add_example(tiny_yolo_v4_device_side_decoding Yolo/tiny_yolo.cpp)
dai_add_example(tiny_yolo_v3_device_side_decoding Yolo/tiny_yolo.cpp)
target_compile_definitions(tiny_yolo_v4_device_side_decoding PRIVATE BLOB_PATH="${tiny_yolo_v4_blob}")
target_compile_definitions(tiny_yolo_v3_device_side_decoding PRIVATE BLOB_PATH="${tiny_yolo_v3_blob}")
dai_add_example(apriltag AprilTag/apriltag.cpp)
dai_add_example(apriltag_rgb AprilTag/apriltag_rgb.cpp)

# DetectionParser
dai_add_example(detection_parser NeuralNetwork/detection_parser.cpp)
target_compile_definitions(detection_parser PRIVATE BLOB_PATH="${mobilenet_blob}")

# DetectionParser
dai_add_example(crash_report CrashReport/crash_report.cpp)

# Sync
dai_add_example(sync_scripts Sync/sync_scripts.cpp)
dai_add_example(demux_message_group Sync/demux_message_group.cpp)
dai_add_example(depth_video_synced Sync/depth_video_synced.cpp)
dai_add_example(imu_video_synced Sync/imu_video_synced.cpp)
