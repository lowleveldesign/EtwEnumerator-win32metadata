#pragma once
#include <tdh.h>

// This is the public extern API for EtwEnumerator for which we create the win32 metadata file.

#pragma warning(push)
#pragma warning(disable:4201)  // nameless struct/union.

class IEtwEnumerator;
enum EtwEventCategory : unsigned;   // Category of event.
enum EtwEnumeratorState : UCHAR;    // Current state of an EtwEnumerator.
struct EtwEventInfo;                // Information about the event: name, provider, etc.
struct EtwAttributeInfo;            // The name and value of an event attribute.
struct EtwRawDataPosition;          // Technical details about the raw event payload.
struct EtwItemInfo;                 // Information about the current item in the event.
struct EtwRawItemInfo;              // Technical details about the current item in the event.
struct EtwStringView;               // Counted string returned from a Format method.
struct EtwStringViewZ;              // Nul-terminated string returned from a Format method.
enum EtwJsonItemFlags : unsigned;   // Selects options to use when formatting an item as JSON.
enum EtwJsonSuffixFlags : unsigned; // Selects the metadata to include in a JSON string.
enum EtwTimestampFormat : unsigned; // Controls timestamp formatting.
using EtwWCHAR = __wchar_t;         // Use native wchar_t for this API.

// using EtwPCWSTR = PCWSTR; // Nul-terminated __wchar_t string.
#define EtwPCWSTR PCWSTR

extern "C" {
    IEtwEnumerator* __stdcall CreateEtwEnumerator();

    void __stdcall DeleteEtwEnumerator(IEtwEnumerator* etwEnumerator);
};

// Please modify methods that return structs to return bool and put the result in an _Out_ pointer parameter AI!
class IEtwEnumerator
{
public:
    virtual EtwEnumeratorState State() const noexcept = 0;

    virtual LSTATUS LastError() const noexcept = 0;

    virtual void Clear() noexcept = 0;

    virtual EtwEventCategory PreviewEvent(
        _In_ EVENT_RECORD const* pEventRecord) noexcept = 0;

    virtual bool StartEvent(
        _In_ EVENT_RECORD const* pEventRecord) noexcept = 0;

    virtual bool StartEventWithTraceEventInfo(
        _In_ EVENT_RECORD const* pEventRecord,
        _In_ TRACE_EVENT_INFO const* pTraceEventInfo) noexcept = 0;

    virtual void Reset() noexcept = 0;

    virtual bool MoveNext() noexcept = 0;

    virtual bool MoveNextSibling() noexcept = 0;

    virtual bool GetEventInfo(_Out_ EtwEventInfo* pEventInfo) const noexcept = 0;

    virtual bool GetItemInfo(_Out_ EtwItemInfo* pItemInfo) const noexcept = 0;

    virtual bool CurrentEventHasEventMessage() const noexcept = 0;

    virtual bool GetRawDataPosition(_Out_ EtwRawDataPosition* pRawDataPosition) const noexcept = 0;

    virtual bool GetRawItemInfo(_Out_ EtwRawItemInfo* pRawItemInfo) const noexcept = 0;

    virtual bool FindCurrentEventAttribute(
        _In_z_ EtwPCWSTR szAttributeName,
        _Out_ EtwStringViewZ* pString) noexcept = 0;

    virtual bool FindEventAttribute(
        _In_opt_z_ EtwPCWSTR szEventAttributes,
        _In_z_ EtwPCWSTR szAttributeName,
        _Out_ EtwStringViewZ* pString) noexcept = 0;

    virtual bool SplitCurrentEventAttributes(
        _Out_writes_to_(cAttributes, *pcAttributes) EtwAttributeInfo* pAttributes,
        unsigned cAttributes,
        _Out_ unsigned* pcAttributes) noexcept = 0;

    virtual bool SplitEventAttributes(
        _In_opt_z_ EtwPCWSTR szEventAttributes,
        _Out_writes_to_(cAttributes, *pcAttributes) EtwAttributeInfo* pAttributes,
        unsigned cAttributes,
        _Out_ unsigned* pcAttributes) noexcept = 0;

    virtual bool FormatCurrentProviderName(
        _Out_ EtwStringViewZ* pString) noexcept = 0;

    virtual bool FormatCurrentEventName(
        _Out_ EtwStringViewZ* pString) noexcept = 0;

    virtual bool FormatCurrentKeywordsName(
        _Out_ EtwStringViewZ* pString) noexcept = 0;

    virtual bool FormatCurrentLevelName(
        _Out_ EtwStringViewZ* pString) noexcept = 0;

    virtual bool FormatCurrentFunctionName(
        _Out_ EtwStringViewZ* pString) noexcept = 0;

    virtual bool FormatCurrentEvent(
        _In_opt_z_ EtwPCWSTR szPrefixFormat,
        EtwJsonSuffixFlags jsonSuffixFlags,
        _Out_ EtwStringViewZ* pString) noexcept = 0;

    virtual bool FormatCurrentEventWithMessage(
        _In_opt_z_ EtwPCWSTR szPrefixFormat,
        _In_z_ EtwPCWSTR szEventMessage,
        _Out_ EtwStringViewZ* pString) noexcept = 0;

    virtual bool FormatCurrentEventPrefix(
        _In_z_ EtwPCWSTR szPrefixFormat,
        _Out_ EtwStringViewZ* pString) noexcept = 0;

    virtual bool FormatCurrentEventAsJson(
        _In_opt_z_ EtwPCWSTR szPrefixFormat,
        EtwJsonSuffixFlags jsonSuffixFlags,
        _Out_ EtwStringViewZ* pString) noexcept = 0;

    virtual bool FormatCurrentItemAsJsonAndMoveNextSibling(
        EtwJsonItemFlags jsonItemFlags,
        _Out_ EtwStringViewZ* pString) noexcept = 0;

    virtual bool FormatCurrentValue(
        _Out_ EtwStringView* pString) noexcept = 0;

    virtual bool FormatValueWithMapName(
        _In_reads_bytes_(cbData) void const* pData,
        unsigned cbData,
        _TDH_IN_TYPE inType,
        _TDH_OUT_TYPE outType,
        _In_ EVENT_RECORD const* pEventRecord,
        _In_opt_ EtwPCWSTR pMapName,
        _Out_ EtwStringView* pString) noexcept = 0;

    virtual bool FormatValueWithMapInfo(
        _In_reads_bytes_(cbData) void const* pData,
        unsigned cbData,
        _TDH_IN_TYPE inType,
        _TDH_OUT_TYPE outType,
        _In_opt_ EVENT_MAP_INFO const* pMapInfo,
        _Out_ EtwStringView* pString) noexcept = 0;

    virtual bool FormatValue(
        _In_reads_bytes_(cbData) void const* pData,
        unsigned cbData,
        _TDH_IN_TYPE inType,
        _TDH_OUT_TYPE outType,
        _Out_ EtwStringView* pString) noexcept = 0;

    virtual unsigned TimerResolution() const noexcept = 0;

    virtual void SetTimerResolution(unsigned value) noexcept = 0;

    virtual unsigned TicksToMilliseconds(unsigned ticks) const noexcept = 0;

    virtual UCHAR PointerSizeFallback() const noexcept = 0;

    virtual void SetPointerSizeFallback(UCHAR value) noexcept = 0;

    virtual EtwTimestampFormat TimestampFormat() const noexcept = 0;

    virtual bool SetTimestampFormat(EtwTimestampFormat value) noexcept = 0;

    virtual int TimeZoneBiasMinutes() const noexcept = 0;

    virtual void SetTimeZoneBiasMinutes(_In_range_(-1440, 1440) int value) noexcept = 0;

    virtual INT64 AdjustFileTimeToLocal(INT64 utcFileTime) const noexcept = 0;
};

/*
The current state of an EtwEnumerator.
Generally refers to the category of the item at which the enumerator is
currently positioned.
*/
enum EtwEnumeratorState
    : UCHAR
{
    EtwEnumeratorState_None,           // After construction, Clear, or failed StartEvent.
    EtwEnumeratorState_Error,          // After an error from a MoveNext operation.
    EtwEnumeratorState_AfterLastItem,  // Positioned after the last item in the event.
    // MoveNext() is an invalid operation for all states above this line.
    // MoveNext() is a valid operation for all states below this line.
    EtwEnumeratorState_BeforeFirstItem,// Positioned before the first item in the event.
    // GetItemInfo() is an invalid operation for all states above this line.
    // GetItemInfo() is a valid operation for all states below this line.
    EtwEnumeratorState_Value,          // Positioned at an item with data (a field or an array element).
    EtwEnumeratorState_ArrayBegin,     // Positioned before the first item in an array.
    EtwEnumeratorState_StructBegin,    // Positioned before the first item in a struct.
    EtwEnumeratorState_ArrayEnd,       // Positioned after the last item in an array.
    EtwEnumeratorState_StructEnd,      // Positioned after the last item in a struct.
};

/*
Options for use when formatting an item as a JSON string with
FormatCurrentItemAsJsonAndMoveNextSibling.
*/
enum EtwJsonItemFlags
    : unsigned
{
    EtwJsonItemFlags_None = 0,
    EtwJsonItemFlags_Name = 0x1,  // Include "FieldName": prefix.
    EtwJsonItemFlags_Space = 0x2, // Add a space after ':' and ',' characters.
};

/*
Flags controlling the metadata to be included in the suffix of a JSON event
string.
*/
enum EtwJsonSuffixFlags
    : unsigned
{
    EtwJsonSuffixFlags_None = 0,         // disable the "meta" section.
    EtwJsonSuffixFlags_provider = 0x1,   // provider name (or GUID if no name).
    EtwJsonSuffixFlags_event = 0x2,      // event name (or IDvVERSION if no name).
    EtwJsonSuffixFlags_time = 0x4,       // timestamp (e.g. "2018-04-01T00:23:38.6676037Z").
    EtwJsonSuffixFlags_cpu = 0x8,        // physical CPU number (decimal integer).
    EtwJsonSuffixFlags_pid = 0x10,       // process ID (decimal integer).
    EtwJsonSuffixFlags_tid = 0x20,       // thread ID (decimal integer).
    EtwJsonSuffixFlags_id = 0x40,        // event ID (decimal integer).
    EtwJsonSuffixFlags_version = 0x80,   // event version (decimal integer, omitted if 0).
    EtwJsonSuffixFlags_channel = 0x100,  // channel (name or decimal integer, omitted if 0).
    EtwJsonSuffixFlags_level = 0x200,    // level (name or decimal integer, omitted if 0).
    EtwJsonSuffixFlags_opcode = 0x400,   // opcode (name or decimal integer, omitted if 0).
    EtwJsonSuffixFlags_task = 0x800,     // task (name or decimal integer, omitted if 0).
    EtwJsonSuffixFlags_keywords = 0x1000,// keywords (name or decimal integer, omitted if 0).
    EtwJsonSuffixFlags_tags = 0x2000,    // event tags (hexadecimal, omitted if 0).
    EtwJsonSuffixFlags_activity = 0x4000,// activity ID (GUID string, omitted if 0).
    EtwJsonSuffixFlags_relatedActivity = 0x8000,// related activity ID (GUID string, omitted if not set).
    EtwJsonSuffixFlags_ktime = 0x10000,  // elapsed kernel time in milliseconds (omitted if unavailable).
    EtwJsonSuffixFlags_utime = 0x20000,  // elapsed user time in milliseconds (omitted if unavailable).
    EtwJsonSuffixFlags_ptime = 0x40000,  // elapsed processor time in CPU ticks (omitted if unavailable).
    EtwJsonSuffixFlags_attribs = 0x80000,// escaped event attributes (omitted if unavailable).
    EtwJsonSuffixFlags_Default = 0xff3f, // Include provider..relatedActivity, except id & version.
    EtwJsonSuffixFlags_All = ~0u
};

/*
General type of an event.
*/
enum EtwEventCategory
    : unsigned
{
    // Invalid event category.
    EtwEventCategory_Error = 0,

    // Event was generated using a TraceMessage-style API. These events
    // generally use TMF-based WPP decoding.
    // Note that TdhGetEventInformation() returns incomplete information for
    // TraceMessage events, and EtwEnumerator will not work correctly with the
    // incomplete information. StartEvent() and StartEventWithTraceEventInfo()
    // will return an error if traceEventInfo.DecodingSource == WPP.
    EtwEventCategory_TmfWpp,

    // Event was generated using a TraceEvent-style API. These events generally
    // use MOF/WBEM decoding. These events are sometimes called "Classic ETW".
    EtwEventCategory_Wbem,

    // Event was generated using an EventWrite-style API but does not include
    // TraceLogging metadata. These events generally use manifest decoding.
    // EventWrite-style events are sometimes called "Crimson ETW".
    EtwEventCategory_Manifest,

    // Event was generated using an EventWrite-style API and includes
    // TraceLogging metadata. These events use TraceLogging decoding.
    // EventWrite-style events are sometimes called "Crimson ETW".
    EtwEventCategory_TraceLogging,

    // Invalid event category.
    EtwEventCategory_Max
};

/*
Specifies timestamp formatting.
*/
enum EtwTimestampFormat
    : unsigned
{
    /*
    No timestamp format type has been set.
    Invalid type - valid format types are greater than this value.
    */
    EtwTimestampFormat_None = 0,

    /*
    Uses Internet Date/Time (rfc3339) format, "2009-06-15T13:45:30.1234567".
    */
    EtwTimestampFormat_Internet,

    /*
    Uses "tracefmt" (traditional WPP) format, "06/15/2009-13:45:30.1234567".
    */
    EtwTimestampFormat_Wpp,

    /*
    Invalid type - valid timestamp format types are less than this value.
    */
    EtwTimestampFormat_Max,

    /*
    If this flag is set, timestamps known to be UTC are converted to local
    time before formatting.
    */
    EtwTimestampFormat_Local = 0x100,

    /*
    By default, SYSTEMTIME is formatted with 3 digits of subsecond precision,
    and FILETIME is formatted with 7 digits of subsecond precision.
    If this flag is set, both SYSTEMTIME and FILETIME timestamps will use 3
    digits of subsecond precision.
    */
    EtwTimestampFormat_LowPrecision = 0x200,

    /*
    By default, timestamps with a known time zone are formatted with a time
    zone suffix. UTC timestamps use "Z" and local timestamps use "+NN:NN",
    e.g. "-08:00", or "+03:30". If this flag is set, no suffix will be used.
    */
    EtwTimestampFormat_NoTimeZoneSuffix = 0x400,

    /*
    By default, TDH_INTYPE_FILETIME and TDH_INTYPE_SYSTEMTIME are assumed to
    be "unspecified time zone" unless they are TDH_OUTTYPE_DATETIME_UTC.
    Set this flag to treat TDH_INTYPE_FILETIME as UTC. (Even with this flag,
    TDH_INTYPE_SYSTEMTIME is still treated as unspecified time zone.)
    */
    EtwTimestampFormat_AssumeFileTimeUTC = 0x800,

    /*
    Default: Internet format, not converted to local time, full precision,
    with "Z" suffix if timestamp is known to be UTC.
    */
    EtwTimestampFormat_Default = EtwTimestampFormat_Internet,

    EtwTimestampFormat_FlagMask = 0xf00,
    EtwTimestampFormat_TypeMask = 0x0ff,
};

/*
Receives information about the event currently being processed.
Note that all of the string fields may be null if the event does not have an
assigned value for the specified field.
*/
struct EtwEventInfo
{
    /*
    The name of the event, or null if the event does not have an assigned name.
    */
    EtwPCWSTR Name;

    union {
        struct {
            /*
            The tags applied to the current event, or 0 if no tags are set.
            */
            UINT32 Tags : 28;
        };
        UINT32 Reserved_Tags;
    };

    /*
    The event's BinaryXml data, or 0/null if event does not have BinaryXml.
    */
    UINT32 BinaryXmlSize;
    _Field_size_bytes_(BinaryXmlSize) void const* BinaryXml;

    GUID const* DecodeGuid;
    GUID const* ControlGuid;

    /*
    The event's task's EventGuid. May be null.
    */
    GUID const* EventGuid;

    EtwPCWSTR ProviderName;
    EtwPCWSTR LevelName;
    EtwPCWSTR ChannelName;
    EtwPCWSTR KeywordsName;
    EtwPCWSTR TaskName;
    EtwPCWSTR OpcodeName;
    EtwPCWSTR EventMessage;
    EtwPCWSTR ProviderMessage;
    EtwPCWSTR EventAttributes;
    EtwPCWSTR WbemActivityIdName;
    EtwPCWSTR WbemRelatedActivityIdName;
};

/*
Receives information about an event attribute.
*/
struct EtwAttributeInfo
{
    EtwPCWSTR Name;
    EtwPCWSTR Value;
};

/*
Receives information about the remaining event payload, i.e. the data that has
not yet been decoded.
*/
struct EtwRawDataPosition
{
    USHORT DataSize;
    _Field_size_bytes_(DataSize) void const* Data;
};

/*
Receives information about the item on which the enumerator is currently
positioned. The meaning of some fields in EtwItemInfo depends on the type of
the current item (i.e. the current State() of the enumerator).
*/
struct EtwItemInfo
{
    /*
    The name of the current item, or "" if item has no name (rare).
    */
    EtwPCWSTR Name;

    union {
        struct {
            /*
            The tags applied to the current field, or 0 if no tags are set.
            */
            UINT32 Tags : 28;

            /*
            If the current item is BeginArray or EndArray, or if the current
            item is an array element, IsArray == 1. Otherwise, IsArray == 0.
            */
            UINT32 IsArray : 1;
        };
        UINT32 Reserved_Tags;
    };

    /*
    The current field's intype.

    The InType here is the canonical intype, which may be different from the
    raw intype. For example, there are several different raw intypes
    representing variations of UNICODESTRING, but all of these raw intypes
    map to the canonical intype for TDH_INTYPE_UNICODESTRING. Since
    EtwEnumerator handles finding the string's data and size, the user does
    not usually need to care about which specific kind of UNICODESTRING was
    used in the raw event.

    If you need access to the original (raw) intype, use GetRawItemInfo.

    Canonical InType         Raw InType(s)
    -------------------------------------------------
    TDH_INTYPE_NULL          TDH_INTYPE_NULL
    TDH_INTYPE_UNICODESTRING TDH_INTYPE_UNICODESTRING
                             TDH_INTYPE_MANIFEST_COUNTEDSTRING
                             TDH_INTYPE_COUNTEDSTRING
                             TDH_INTYPE_REVERSEDCOUNTEDSTRING
                             TDH_INTYPE_NONNULLTERMINATEDSTRING
    TDH_INTYPE_ANSISTRING    TDH_INTYPE_ANSISTRING
                             TDH_INTYPE_MANIFEST_COUNTEDANSISTRING
                             TDH_INTYPE_COUNTEDANSISTRING
                             TDH_INTYPE_REVERSEDCOUNTEDANSISTRING
                             TDH_INTYPE_NONNULLTERMINATEDANSISTRING
    TDH_INTYPE_INT8          TDH_INTYPE_INT8
    TDH_INTYPE_UINT8         TDH_INTYPE_UINT8
    TDH_INTYPE_INT16         TDH_INTYPE_INT16
    TDH_INTYPE_UINT16        TDH_INTYPE_UINT16
    TDH_INTYPE_INT32         TDH_INTYPE_INT32
    TDH_INTYPE_UINT32        TDH_INTYPE_UINT32
    TDH_INTYPE_INT64         TDH_INTYPE_INT64
    TDH_INTYPE_UINT64        TDH_INTYPE_UINT64
    TDH_INTYPE_FLOAT         TDH_INTYPE_FLOAT
    TDH_INTYPE_DOUBLE        TDH_INTYPE_DOUBLE
    TDH_INTYPE_BOOLEAN       TDH_INTYPE_BOOLEAN
    TDH_INTYPE_BINARY        TDH_INTYPE_BINARY
                             TDH_INTYPE_MANIFEST_COUNTEDBINARY
                             TDH_INTYPE_HEXDUMP
    TDH_INTYPE_GUID          TDH_INTYPE_GUID
    TDH_INTYPE_POINTER       TDH_INTYPE_POINTER
    TDH_INTYPE_FILETIME      TDH_INTYPE_FILETIME
    TDH_INTYPE_SYSTEMTIME    TDH_INTYPE_SYSTEMTIME
    TDH_INTYPE_SID           TDH_INTYPE_SID
                             TDH_INTYPE_WBEMSID
    TDH_INTYPE_HEXINT32      TDH_INTYPE_HEXINT32
    TDH_INTYPE_HEXINT64      TDH_INTYPE_HEXINT64
    TDH_INTYPE_UNICODECHAR   TDH_INTYPE_UNICODECHAR
    TDH_INTYPE_ANSICHAR      TDH_INTYPE_ANSICHAR
    TDH_INTYPE_SIZET         TDH_INTYPE_SIZET
    */
    _TDH_IN_TYPE  InType : 16;

    /*
    The current field's outtype.
    */
    _TDH_OUT_TYPE OutType : 16;

    /*
    If IsArray is true, contains the array index. Otherwise 0. Specifically:
    - For BeginArray state: ArrayIndex == 0.
    - For EndArray state: ArrayIndex == ArrayCount.
    - For array elements: the element's array index.
    - Otherwise: 0.
    */
    USHORT ArrayIndex;

    /*
    If IsArray is true, contains the array length. Otherwise 1.
    */
    USHORT ArrayCount;

    /*
    If the current item's data type has a fixed size (e.g. INT8, INT32, GUID),
    ElementSize is the size of a single item of this type (e.g. 1 for INT8, 4
    for INT32, 16 for GUID).
    If the current item's data type has a variable size (e.g. string, binary,
    sid, struct), ElementSize is 0.
    */
    USHORT ElementSize;

    /*
    For Value state: DataSize = the size of the current item's Data.
    For BeginArray state: DataSize = ArrayCount * ElementSize.
    For other states: DataSize = 0.

    Data points into the buffer of pEventRecord. The pointer may be unaligned
    and will become invalid when pEventRecord becomes invalid.

    For some data types, the Data field excludes a portion of the raw encoded
    data:
    - For nul-terminated strings, Data does not include the nul termination.
    - For counted string, Data does not include the count.
    - For counted binary, Data does not include the count.
    - For WBEMSID, Data points at the SID (does not include the TOKEN_USER).
    */
    USHORT DataSize;
    _Field_size_bytes_(DataSize) void const* Data;

    /*
    If the value is an enumeration or bitfield with a map, MapName contains
    the name of the map for use with TdhGetEventMapInformation(). Otherwise,
    MapName is null.
    */
    EtwPCWSTR MapName;
};

/*
Receives technical details about the item on which the enumerator is currently
positioned. The meaning of some fields in EtwRawItemInfo depends on the type
of the current item (i.e. the current State() of the enumerator).
*/
struct EtwRawItemInfo
{
    union {
        struct {
            /*
            EtwItemInfo::InType returns a canonical intype value, i.e. several
            different variations of utf-16le strings are reduced to the single
            type TDH_INTYPE_UNICODESTRING. EtwRawItemInfo::RawInType returns
            the original (raw) intype of the event.
            */
            _TDH_IN_TYPE RawInType : 16;

            /*
            The property flags set for the current item.
            */
            PROPERTY_FLAGS Flags : 16;
        };
        UINT32 Reserved_RawInType;
    };

    /*
    EtwItemInfo::Data sometimes skips certain parts of the raw event data such
    as the raw size prefix or the string's nul termination.
    EtwRawItemInfo::RawData presents the full binary field value, including
    size prefix and nul termination.
    */
    UINT32 RawDataSize;
    _Field_size_bytes_(RawDataSize) void const* RawData;

    /*
    Pointer to the field's custom schema information, or null if the field
    does not have custom schema information. Custom schema information is
    rarely used, so this will almost always be null.

    Custom schema information is decoding information for use by another tool.
    Some fields contain encoded data that can be processed by another tool,
    e.g. binary data packed using a serialization system such as Protocol
    Buffers or Bond. These fields will be encoded using a normal ETW intype
    (e.g. BINARY), but can contain schema information to be passed to the
    deserialization tool. If such as system is in use, the CustomSchema
    pointer will point at the schema data. The schema data is a structure
    laid out as follows:

    UINT16 Protocol; // User-defined protocol identifier 5..31
    UINT16 Length;
    BYTE SchemaData[Length]; // Decoding information for the decoding tool.
    */
    void const* CustomSchema;
};

/*
Receives a pointer to a counted string and a length.
Note that ETW supports strings with embedded nul characters. The string
referenced by this structure will not be nul-terminated and may contain
embedded nul characters. Use DataLength instead of assuming the string is
nul-terminated.
*/
struct EtwStringView
{
    _Field_size_(DataLength) EtwWCHAR const* Data;
    UINT32 DataLength;
};

/*
Receives a pointer to a nul-terminated string and a length. The nul
termination character is not included in the length, i.e. the nul termination
will always be at position Data[DataLength].
*/
struct EtwStringViewZ
{
    _Field_size_(DataLength + 1) EtwPCWSTR Data;
    UINT32 DataLength;
};

#pragma warning(pop)
