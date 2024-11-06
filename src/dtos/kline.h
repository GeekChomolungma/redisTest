#ifndef KLINE_H
#define KLINE_H

#include <cstdint>
#include <nlohmann/json.hpp>
#include <iostream>

class Kline {
public:
    // kline info
    char Id[12];
    int64_t StartTime;
    int64_t EndTime;
    char Symbol[16];
    char Interval[16];
    int64_t FirstTradeID;
    int64_t LastTradeID;
    double  Open;
    double  Close;
    double  High;
    double  Low;
    double  Volume;
    int64_t  TradeNum;
    bool IsFinal;
    double  QuoteVolume;
    double  ActiveBuyVolume;
    double  ActiveBuyQuoteVolume;
    double  TrueRange;

    // SuperTrend Indicator
    // need to calculate if length is change
    double  AveTrueRange;
    double  SuperTrendValue;
    double  StUp;
    double  StDown;
    int     STDirection; // -1 1
    int     Action; // 0 is none, 1 is sell, 2 is buy
};

class KlineResponse {
public:
    // kline info
    char EventType[16];           // "e": "kline" - Event type
    int64_t EventTime;           // "E": 1672515782136 - Event time
    char Symbol[16];             // "s": "BNBBTC" - Trading pair
    int64_t StartTime;           // "t": 1672515780000 - Start time of this Kline
    int64_t EndTime;             // "T": 1672515839999 - End time of this Kline
    char Interval[16];           // "i": "1m" - Kline interval
    int64_t FirstTradeID;        // "f": 100 - First trade ID during this Kline
    int64_t LastTradeID;         // "L": 200 - Last trade ID during this Kline
    std::string Open;            // "o": "0.0010" - Opening price
    std::string Close;           // "c": "0.0020" - Closing price
    std::string High;            // "h": "0.0025" - Highest price during this Kline
    std::string Low;             // "l": "0.0015" - Lowest price during this Kline
    std::string Volume;          // "v": "1000" - Volume during this Kline
    int64_t TradeNum;            // "n": 100 - Number of trades during this Kline
    bool IsFinal;                // "x": false - Whether this Kline is final
    std::string QuoteVolume;     // "q": "1.0000" - Quote asset volume during this Kline
    std::string ActiveBuyVolume; // "V": "500" - Volume of active buy during this Kline
    std::string ActiveBuyQuoteVolume; // "Q": "0.500" - Quote asset volume of active buy during this Kline
    int64_t IgnoreParam;         // "B": "123456" - Ignore this parameter

    // Serialization/Deserialization methods
    static KlineResponse deserializeFromJson(const nlohmann::json& j) {
        KlineResponse kline;
        if (j.contains("e") && j["e"].is_string()) {
            std::strncpy(kline.EventType, j["e"].get<std::string>().c_str(), sizeof(kline.EventType));
        } else {
            std::cerr << "Missing or invalid type for 'e'" << std::endl;
        }

        if (j.contains("E") && j["E"].is_number_integer()) {
            kline.EventTime = j["E"].get<int64_t>();
        } else {
            std::cerr << "Missing or invalid type for 'E'" << std::endl;
        }

        if (j.contains("s") && j["s"].is_string()) {
            std::strncpy(kline.Symbol, j["s"].get<std::string>().c_str(), sizeof(kline.Symbol));
        } else {
            std::cerr << "Missing or invalid type for 's'" << std::endl;
        }

        if (j.contains("k") && j["k"].is_object()) {
            const auto& k = j["k"];

            if (k.contains("t") && k["t"].is_number_integer()) {
                kline.StartTime = k["t"].get<int64_t>();
            } else {
                std::cerr << "Missing or invalid type for 't'" << std::endl;
            }

            if (k.contains("T") && k["T"].is_number_integer()) {
                kline.EndTime = k["T"].get<int64_t>();
            } else {
                std::cerr << "Missing or invalid type for 'T'" << std::endl;
            }

            if (k.contains("i") && k["i"].is_string()) {
                std::strncpy(kline.Interval, k["i"].get<std::string>().c_str(), sizeof(kline.Interval));
            } else {
                std::cerr << "Missing or invalid type for 'i'" << std::endl;
            }

            if (k.contains("f") && k["f"].is_number_integer()) {
                kline.FirstTradeID = k["f"].get<int64_t>();
            } else {
                std::cerr << "Missing or invalid type for 'f'" << std::endl;
            }

            if (k.contains("L") && k["L"].is_number_integer()) {
                kline.LastTradeID = k["L"].get<int64_t>();
            } else {
                std::cerr << "Missing or invalid type for 'L'" << std::endl;
            }

            if (k.contains("o") && k["o"].is_string()) {
                kline.Open = k["o"].get<std::string>();
            } else {
                std::cerr << "Missing or invalid type for 'o'" << std::endl;
            }

            if (k.contains("c") && k["c"].is_string()) {
                kline.Close = k["c"].get<std::string>();
            } else {
                std::cerr << "Missing or invalid type for 'c'" << std::endl;
            }

            if (k.contains("h") && k["h"].is_string()) {
                kline.High = k["h"].get<std::string>();
            } else {
                std::cerr << "Missing or invalid type for 'h'" << std::endl;
            }

            if (k.contains("l") && k["l"].is_string()) {
                kline.Low = k["l"].get<std::string>();
            } else {
                std::cerr << "Missing or invalid type for 'l'" << std::endl;
            }

            if (k.contains("v") && k["v"].is_string()) {
                kline.Volume = k["v"].get<std::string>();
            } else {
                std::cerr << "Missing or invalid type for 'v'" << std::endl;
            }

            if (k.contains("n") && k["n"].is_number_integer()) {
                kline.TradeNum = k["n"].get<int64_t>();
            } else {
                std::cerr << "Missing or invalid type for 'n'" << std::endl;
            }

            if (k.contains("x") && k["x"].is_boolean()) {
                kline.IsFinal = k["x"].get<bool>();
            } else {
                std::cerr << "Missing or invalid type for 'x'" << std::endl;
            }

            if (k.contains("q") && k["q"].is_string()) {
                kline.QuoteVolume = k["q"].get<std::string>();
            } else {
                std::cerr << "Missing or invalid type for 'q'" << std::endl;
            }

            if (k.contains("V") && k["V"].is_string()) {
                kline.ActiveBuyVolume = k["V"].get<std::string>();
            } else {
                std::cerr << "Missing or invalid type for 'V'" << std::endl;
            }

            if (k.contains("Q") && k["Q"].is_string()) {
                kline.ActiveBuyQuoteVolume = k["Q"].get<std::string>();
            } else {
                std::cerr << "Missing or invalid type for 'Q'" << std::endl;
            }

            // if (k.contains("B") && k["B"].is_number_integer()) {
            //     kline.IgnoreParam = k["B"].get<int64_t>();
            // } else {
            //     std::cerr << "Missing or invalid type for 'B'" << std::endl;
            // }
        } else {
            std::cerr << "Missing or invalid type for 'k'" << std::endl;
        }

        return kline;
    }

    static nlohmann::json serializeToJson(const KlineResponse& kline) {
        nlohmann::json j;
        j["e"] = kline.EventType;
        j["E"] = kline.EventTime;
        j["s"] = kline.Symbol;
        j["k"] = {
            {"t", kline.StartTime},
            {"T", kline.EndTime},
            {"s", kline.Symbol},
            {"i", kline.Interval},
            {"f", kline.FirstTradeID},
            {"L", kline.LastTradeID},
            {"o", kline.Open},
            {"c", kline.Close},
            {"h", kline.High},
            {"l", kline.Low},
            {"v", kline.Volume},
            {"n", kline.TradeNum},
            {"x", kline.IsFinal},
            {"q", kline.QuoteVolume},
            {"V", kline.ActiveBuyVolume},
            {"Q", kline.ActiveBuyQuoteVolume},
            // {"B", kline.IgnoreParam}
        };
        return j;
    }
};


#endif
