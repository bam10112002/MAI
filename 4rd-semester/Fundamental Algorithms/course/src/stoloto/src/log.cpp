// #include "log.h"

// // static void Log::Winnigs (const u32&, const std::string&){}
// // static void Log::Saled   (const u32&, const std::string&){}
// // static void Log::DrawSize(const u32& size, const std::string& path)
// // {
// //     json j = {}
// //     log["drawSize"] = size;
// //     std::ofstream of(path);
// //     of << log;
// // }
// // static void Log::FileSize(const u32& size, const std::string& path)
// // {
// //     json j = {}
// //     log["fileSize"] = size;
// //     std::ofstream of(path);
// //     of << log;
// // }
// // static void Log::Cost    (const u32&, const std::string&){}
// // static void Log::WinVec(const std::vector<int>&, const std::string&){}
// // static void Log::WinVec(const std::vector<std::vector<int>>&, const std::string&){}

// static u32 DrawSize(std::string path)
// {
//     std::fstream ifs(path);
//     if (!ifs.open())
//         // TODO: ERROR
//     json log = {};
//     ifs >> log;
//     return log["drawSize"];
// }
// static u32 FileSize(std::string path)
// {
//     std::fstream ifs(path);
//     if (!ifs.open())
//         // TODO: ERROR
//     json log = {};
//     ifs >> log;
//     return log["fileSize"];
// }