#pragma once

#include "IDirectory.h"
#include "IFile.h"
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

namespace aoc_2022_7 {

class Directory : public IDirectory {
public:
    Directory(std::string_view name, IDirectory* parentDir = nullptr);
    ~Directory() override = default;
    Directory(const Directory&) = default;
    Directory& operator=(const Directory&) = delete;
    Directory(Directory&&) = default;
    Directory& operator=(Directory&&) = delete;
    uint32_t getSize() override;
    std::string_view getName() const override;
    IDirectory& addDirectory(std::string_view name) override;
    IFile& addFile(std::string_view name, uint32_t size) override;
    IDirectory* getParentDirectory() const override;
    std::vector<IDirectory*> getChildDirectories() const override;

private:
    uint32_t calculateSize() const;

    std::unordered_map<std::string, std::unique_ptr<IDirectory>> mDirs{};
    std::unordered_map<std::string, std::unique_ptr<IFile>> mFiles{};
    IDirectory* mParentDir;
    const std::string mName;
    std::optional<uint32_t> mCachedSize{};
};

} // namespace aoc_2022_7
