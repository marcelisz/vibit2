#ifndef _CONFIGURE_H_
#define _CONFIGURE_H_
/** Configure processes settings related to the teletext service and vbit2 command line options.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdint.h>
#include <cstring>
#include <sys/stat.h>
#include <vector>
#include <array>
#include <algorithm>
#include <stdexcept>
#include <memory>

#include "debug.h"
#include "ttxline.h"
#include "datelang.h"

#define CONFIGFILE "vbit.conf" // default config file name

namespace vbit

{
/** An optional text message which scrolls through the place of the clock in the
 *  page header every so often.
 */
struct ClockMessage
{
    std::string text;         //!< the message in teletext characters, empty when disabled
    double speed;             //!< scrolling speed in characters per second
    unsigned int frequency;   //!< seconds of clock before the message appears again
};

class Configure
{
    public:
        enum OutputFormat
        {
            None,
            T42,
            Raw,
            TS,
            TSNPTS
        };
        
        /** How the magazines are scheduled for transmission.
         *  Parallel divides the VBI lines between all the magazines.
         *  Serial transmits one complete magazine at a time.
         */
        enum MagazineBroadcastMode
        {
            MAGAZINE_PARALLEL,
            MAGAZINE_SERIAL
        };
        
        //Configure();
        /** Constructor can take overrides from the command line
         */
        Configure(Debug *debug, int argc=0, char** argv=NULL);
        ~Configure();
        
        inline std::string GetPageDirectory(){return _pageDir;};
        
        std::string GetHeaderTemplate(){return _headerTemplate;}
        void SetHeaderTemplate(std::shared_ptr<TTXLine> line);
        bool GetRowAdaptive(){return _rowAdaptive;}
        void SetRowAdaptive(bool flag){_rowAdaptive = flag;}
        MagazineBroadcastMode GetMagazineBroadcastMode(){return _magazineBroadcastMode;}
        bool GetReversePageBroadcast(){return _reversePageBroadcast;}
        const DateLanguage* GetDateLanguage(){return _dateLanguage;}
        bool GetDateRegionExplicit(){return _dateRegionExplicit;}
        const ClockMessage* GetClockMessage(){return _clockMessage.text.empty() ? nullptr : &_clockMessage;}
        std::string GetServiceStatusString(){return _serviceStatusString;}
        void SetServiceStatusString(std::string status){status.resize(20,' '); _serviceStatusString = status;}
        /** Set the 20 character status display from a teletext line.
         *  Control codes are expanded from the escape sequences in the same way
         *  as the header template.
         */
        void SetServiceStatusString(std::shared_ptr<TTXLine> line);
        bool GetMultiplexedSignalFlag(){return _multiplexedSignalFlag;}
        uint16_t GetNetworkIdentificationCode(){return _NetworkIdentificationCode;}
        std::array<uint8_t, 4> GetReservedBytes(){return _reservedBytes;}
        void SetReservedBytes(std::array<uint8_t, 4> reserved){_reservedBytes = reserved;}
        uint8_t GetInitialMag(){return _initialMag;}
        uint8_t GetInitialPage(){return _initialPage;}
        uint16_t GetInitialSubcode(){return _initialSubcode;}
        uint16_t GetLinesPerField(){return _linesPerField;}
        uint16_t GetDatacastLines(){return _datacastLines;}
        bool GetReverseFlag(){return _reverseBits;}
        int GetMagazinePriority(uint8_t mag){return _magazinePriority[mag];}
        
        OutputFormat GetOutputFormat(){return _OutputFormat;}
        uint16_t GetTSPID(){return _PID;}
        
        uint16_t GetPacketServerPort(){return _packetServerPort;}
        bool GetPacketServerEnabled(){return _packetServerPort != 0;}
        uint16_t GetPacketServerMaxClients(){return _packetServerMaxClients;}
        
        uint16_t GetInterfaceServerPort(){return _interfaceServerPort;}
        bool GetInterfaceServerEnabled(){return _interfaceServerPort != 0;}
        uint16_t GetInterfaceServerMaxClients(){return _interfaceServerMaxClients;}
        
    private:
        Debug* _debug;
        int DirExists(std::string *path);
        
        int LoadConfigFile(std::string filename);
        
        // template string for generating header packets
        std::string _headerTemplate;
        
        bool _rowAdaptive;
        uint16_t _linesPerField;
        uint16_t _datacastLines;
        MagazineBroadcastMode _magazineBroadcastMode;
        bool _reversePageBroadcast;
        
        // language used for the day and month names in the page header
        std::string _dateRegion;
        const DateLanguage* _dateLanguage;
        bool _dateRegionExplicit; // true when date_region was set in the config file
        
        // optional message which scrolls through the clock in the page header
        ClockMessage _clockMessage;     // as used for transmission
        std::string _clockMessageText;  // as read from the config file, in UTF-8
        
        // settings for generation of packet 8/30
        bool _multiplexedSignalFlag; // false indicates teletext is multiplexed with video, true means full frame teletext.
        int _magazinePriority[8];
        uint8_t _initialMag;
        uint8_t _initialPage;
        uint16_t _initialSubcode;
        uint16_t _NetworkIdentificationCode;
        uint16_t _CountryNetworkIdentificationCode;
        std::array<uint8_t, 4> _reservedBytes; // four bytes which the teletext specification marks reserved
        std::string _serviceStatusString; /// 20 characters
        
        std::string _configFile; /// Configuration file name --config
        std::string _pageDir; /// Configuration file name --dir
        bool _reverseBits;
        
        OutputFormat _OutputFormat;
        uint16_t _PID;
        
        uint16_t _packetServerPort;
        uint16_t _packetServerMaxClients;
        uint16_t _interfaceServerPort;
        uint16_t _interfaceServerMaxClients;
    };
}

#endif
