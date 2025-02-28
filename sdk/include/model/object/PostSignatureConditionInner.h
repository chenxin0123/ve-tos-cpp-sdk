#pragma once

#include <string>
#include <utility>
#include <memory>
namespace VolcengineTos {
class PostSignatureConditionInner {
public:
    PostSignatureConditionInner(std::shared_ptr<std::string> anOperator, std::string key, std::string value)
            : operator_(std::move(anOperator)), key_(std::move(key)), value_(std::move(value)) {
    }
    PostSignatureConditionInner(std::string key, std::string value) : key_(std::move(key)), value_(std::move(value)) {
    }
    PostSignatureConditionInner() = default;
    virtual ~PostSignatureConditionInner() = default;
    const std::string& getKey() const {
        return key_;
    }
    void setKey(const std::string& key) {
        key_ = key;
    }
    const std::string& getValue() const {
        return value_;
    }
    void setValue(const std::string& value) {
        value_ = value;
    }
    const std::shared_ptr<std::string>& getAnOperator() const {
        return operator_;
    }
    void setAnOperator(const std::shared_ptr<std::string>& anOperator) {
        operator_ = anOperator;
    }

private:
    std::shared_ptr<std::string> operator_ = nullptr;
    std::string key_;
    std::string value_;
};
}  // namespace VolcengineTos
