#include "qrcodegen.hpp"
#include "ylang/vm.hpp"
using namespace qrcodegen;
#include <iostream>

extern "C" void YlangLoadModule(std::shared_ptr<Env> env, const std::vector<std::string> &symbols) {
    auto moduleNamespace = std::make_shared<ClassObject>("QRgen");
		moduleNamespace->mro.push_back(moduleNamespace.get());
		auto define = [&](string name, NativeFunc f) {
			moduleNamespace->staticFields[name] = Value::Native(f);
			if (symbols.size() == 1 && symbols[0] == "*") {
				env->set(name, Value::Native(f), true);
				return;
			}
			for (const auto &s : symbols)
				if (s == name) {
					env->set(name, Value::Native(f), true);
					break;
				}
		};
		static auto QrClass = std::make_shared<ClassObject>("QRcode");
		auto QrToValue = [=](QrCode qr, int l, int c) -> Value {
			auto inst = std::make_shared<InstanceObject>(QrClass.get());
			inst->fields["Version"] = Value::Int(qr.getVersion());
			inst->fields["Size"] = Value::Int(qr.getSize());
			std::vector<Value> arr;
			arr.reserve(qr.getSize());
			for (int x = 0; x < qr.getSize(); x++) {
				std::vector<Value> temp;
				temp.reserve(qr.getSize());
				for (int y = 0; y < qr.getSize(); y++) {
					temp.push_back(Value::Bool(qr.getModule(x, y)));
				}
				arr.push_back(Value::Tuple(temp));
			}
			inst->fields["BoolArray"] = Value::Tuple(arr);
			inst->fields["CorrectionLevel"] =
				Value::Int(static_cast<long long>(qr.getErrorCorrectionLevel()));
			Value v;
			v.type = ValueType::INSTANCE;
			v.ref = inst;
			return v;
		};
		env->set("ECC_LEVEL_LOW",
			Value::Int(static_cast<long long>(QrCode::Ecc::LOW)), true,
			true);
		env->set("ECC_LEVEL_MEDIUM",
			Value::Int(static_cast<long long>(QrCode::Ecc::MEDIUM)), true,
			true);
		env->set("ECC_LEVEL_QUARTILE",
			Value::Int(static_cast<long long>(QrCode::Ecc::QUARTILE)), true,
			true);
		env->set("ECC_LEVEL_HIGH",
			Value::Int(static_cast<long long>(QrCode::Ecc::HIGH)), true,
			true);
		define("GenerateQRcode", [=](const vector<Value> &args, int l, int c) {
			if (args.size() != 2)
				throw ArgumentError("EncodeText(text, encodeLevel)", l, c);
			QrCode QR =
				QrCode::encodeText(args[0].asString().c_str(),
					static_cast<QrCode::Ecc>(args[1].asInt()));
			return QrToValue(QR, l, c);
		});
		Value modVal;
		modVal.type = ValueType::CLASS;
		modVal.ref = moduleNamespace;
		env->set("QRgen", modVal, false, false);
	}
