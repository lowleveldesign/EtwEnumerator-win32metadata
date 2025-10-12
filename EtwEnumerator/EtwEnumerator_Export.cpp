#include "stdafx.h"
#include "EtwEnumerator.h"
#include <new>

class IEtwEnumeratorImpl : public IEtwEnumerator
{
public:
    IEtwEnumeratorImpl() : etwEnumerator(new EtwEnumerator()) {}
    ~IEtwEnumeratorImpl() {
        delete etwEnumerator;
    }

    virtual EtwEnumeratorState State() const noexcept override {
        return etwEnumerator->State();
    }

    virtual LSTATUS LastError() const noexcept override {
        return etwEnumerator->LastError();
    }

    virtual void Clear() noexcept override {
        etwEnumerator->Clear();
    }

    virtual EtwEventCategory PreviewEvent(
        _In_ EVENT_RECORD const* pEventRecord) noexcept override {
        return etwEnumerator->PreviewEvent(pEventRecord);
    }

    virtual bool StartEvent(
        _In_ EVENT_RECORD const* pEventRecord) noexcept override {
        return etwEnumerator->StartEvent(pEventRecord);
    }

    virtual bool StartEventWithTraceEventInfo(
        _In_ EVENT_RECORD const* pEventRecord,
        _In_ TRACE_EVENT_INFO const* pTraceEventInfo) noexcept override {
        return etwEnumerator->StartEventWithTraceEventInfo(pEventRecord, pTraceEventInfo);
    }

    virtual void Reset() noexcept override {
        etwEnumerator->Reset();
    }

    virtual bool MoveNext() noexcept override {
        return etwEnumerator->MoveNext();
    }

    virtual bool MoveNextSibling() noexcept override {
        return etwEnumerator->MoveNextSibling();
    }

    virtual bool GetEventInfo(_Out_ EtwEventInfo* pEventInfo) const noexcept override {
        *pEventInfo = etwEnumerator->GetEventInfo();
        return pEventInfo != nullptr;
    }

    virtual bool GetItemInfo(_Out_ EtwItemInfo* pItemInfo) const noexcept override {
        *pItemInfo = etwEnumerator->GetItemInfo();
        return pItemInfo != nullptr;
    }

    virtual bool CurrentEventHasEventMessage() const noexcept override {
        return etwEnumerator->CurrentEventHasEventMessage();
    }

    virtual bool GetRawDataPosition(EtwRawDataPosition* pRawDataPosition) const noexcept override {
        *pRawDataPosition = etwEnumerator->GetRawDataPosition();
        return pRawDataPosition != nullptr;
    }

    virtual bool GetRawItemInfo(EtwRawItemInfo* pRawItemInfo) const noexcept override {
        *pRawItemInfo = etwEnumerator->GetRawItemInfo();
        return pRawItemInfo != nullptr;
    }

    virtual bool FindCurrentEventAttribute(
        _In_z_ EtwPCWSTR szAttributeName,
        _Out_ EtwStringViewZ* pString) noexcept override {
        return etwEnumerator->FindCurrentEventAttribute(szAttributeName, pString);
    }

    virtual bool FindEventAttribute(
        _In_opt_z_ EtwPCWSTR szEventAttributes,
        _In_z_ EtwPCWSTR szAttributeName,
        _Out_ EtwStringViewZ* pString) noexcept override {
        return etwEnumerator->FindEventAttribute(szEventAttributes, szAttributeName, pString);
    }

    virtual bool SplitCurrentEventAttributes(
        _Out_writes_to_(cAttributes, *pcAttributes) EtwAttributeInfo* pAttributes,
        unsigned cAttributes,
        _Out_ unsigned* pcAttributes) noexcept override {
        return etwEnumerator->SplitCurrentEventAttributes(pAttributes, cAttributes, pcAttributes);
    }

    virtual bool SplitEventAttributes(
        _In_opt_z_ EtwPCWSTR szEventAttributes,
        _Out_writes_to_(cAttributes, *pcAttributes) EtwAttributeInfo* pAttributes,
        unsigned cAttributes,
        _Out_ unsigned* pcAttributes) noexcept override {
        return etwEnumerator->SplitEventAttributes(szEventAttributes, pAttributes, cAttributes, pcAttributes);
    }

    virtual bool FormatCurrentProviderName(
        _Out_ EtwStringViewZ* pString) noexcept override {
        return etwEnumerator->FormatCurrentProviderName(pString);
    }

    virtual bool FormatCurrentEventName(
        _Out_ EtwStringViewZ* pString) noexcept override {
        return etwEnumerator->FormatCurrentEventName(pString);
    }

    virtual bool FormatCurrentKeywordsName(
        _Out_ EtwStringViewZ* pString) noexcept override {
        return etwEnumerator->FormatCurrentKeywordsName(pString);
    }

    virtual bool FormatCurrentLevelName(
        _Out_ EtwStringViewZ* pString) noexcept override {
        return etwEnumerator->FormatCurrentLevelName(pString);
    }

    virtual bool FormatCurrentFunctionName(
        _Out_ EtwStringViewZ* pString) noexcept override {
        return etwEnumerator->FormatCurrentFunctionName(pString);
    }

    virtual bool FormatCurrentEvent(
        _In_opt_z_ EtwPCWSTR szPrefixFormat,
        EtwJsonSuffixFlags jsonSuffixFlags,
        _Out_ EtwStringViewZ* pString) noexcept override {
        return etwEnumerator->FormatCurrentEvent(szPrefixFormat, jsonSuffixFlags, pString);
    }

    virtual bool FormatCurrentEventWithMessage(
        _In_opt_z_ EtwPCWSTR szPrefixFormat,
        _In_z_ EtwPCWSTR szEventMessage,
        _Out_ EtwStringViewZ* pString) noexcept override {
        return etwEnumerator->FormatCurrentEventWithMessage(szPrefixFormat, szEventMessage, pString);
    }

    virtual bool FormatCurrentEventPrefix(
        _In_z_ EtwPCWSTR szPrefixFormat,
        _Out_ EtwStringViewZ* pString) noexcept override {
        return etwEnumerator->FormatCurrentEventPrefix(szPrefixFormat, pString);
    }

    virtual bool FormatCurrentEventAsJson(
        _In_opt_z_ EtwPCWSTR szPrefixFormat,
        EtwJsonSuffixFlags jsonSuffixFlags,
        _Out_ EtwStringViewZ* pString) noexcept override {
        return etwEnumerator->FormatCurrentEventAsJson(szPrefixFormat, jsonSuffixFlags, pString);
    }

    virtual bool FormatCurrentItemAsJsonAndMoveNextSibling(
        EtwJsonItemFlags jsonItemFlags,
        _Out_ EtwStringViewZ* pString) noexcept override {
        return etwEnumerator->FormatCurrentItemAsJsonAndMoveNextSibling(jsonItemFlags, pString);
    }

    virtual bool FormatCurrentValue(
        _Out_ EtwStringView* pString) noexcept override {
        return etwEnumerator->FormatCurrentValue(pString);
    }

    virtual bool FormatValueWithMapName(
        _In_reads_bytes_(cbData) void const* pData,
        unsigned cbData,
        _TDH_IN_TYPE inType,
        _TDH_OUT_TYPE outType,
        _In_ EVENT_RECORD const* pEventRecord,
        _In_opt_ EtwPCWSTR pMapName,
        _Out_ EtwStringView* pString) noexcept override {
        return etwEnumerator->FormatValueWithMapName(pData, cbData, inType, outType, pEventRecord, pMapName, pString);
    }

    virtual bool FormatValueWithMapInfo(
        _In_reads_bytes_(cbData) void const* pData,
        unsigned cbData,
        _TDH_IN_TYPE inType,
        _TDH_OUT_TYPE outType,
        _In_opt_ EVENT_MAP_INFO const* pMapInfo,
        _Out_ EtwStringView* pString) noexcept override {
        return etwEnumerator->FormatValueWithMapInfo(pData, cbData, inType, outType, pMapInfo, pString);
    }

    virtual bool FormatValue(
        _In_reads_bytes_(cbData) void const* pData,
        unsigned cbData,
        _TDH_IN_TYPE inType,
        _TDH_OUT_TYPE outType,
        _Out_ EtwStringView* pString) noexcept override {
        return etwEnumerator->FormatValue(pData, cbData, inType, outType, pString);
    }

    virtual unsigned TimerResolution() const noexcept override {
        return etwEnumerator->TimerResolution();
    }

    virtual void SetTimerResolution(unsigned value) noexcept override {
        etwEnumerator->SetTimerResolution(value);
    }

    virtual unsigned TicksToMilliseconds(unsigned ticks) const noexcept override {
        return etwEnumerator->TicksToMilliseconds(ticks);
    }

    virtual UCHAR PointerSizeFallback() const noexcept override {
        return etwEnumerator->PointerSizeFallback();
    }

    virtual void SetPointerSizeFallback(UCHAR value) noexcept override {
        etwEnumerator->SetPointerSizeFallback(value);
    }

    virtual EtwTimestampFormat TimestampFormat() const noexcept override {
        return etwEnumerator->TimestampFormat();
    }

    virtual bool SetTimestampFormat(EtwTimestampFormat value) noexcept override {
        return etwEnumerator->SetTimestampFormat(value);
    }

    virtual int TimeZoneBiasMinutes() const noexcept override {
        return etwEnumerator->TimeZoneBiasMinutes();
    }

    virtual void SetTimeZoneBiasMinutes(_In_range_(-1440, 1440) int value) noexcept override {
        etwEnumerator->SetTimeZoneBiasMinutes(value);
    }

    virtual INT64 AdjustFileTimeToLocal(INT64 utcFileTime) const noexcept override {
        return etwEnumerator->AdjustFileTimeToLocal(utcFileTime);
    }

private:
    EtwEnumerator* etwEnumerator;
};

extern "C" {
    IEtwEnumerator* __stdcall CreateEtwEnumerator() {
        return new (std::nothrow) IEtwEnumeratorImpl();
    }

    void __stdcall DeleteEtwEnumerator(IEtwEnumerator* etwEnumerator) {
        // FIXME: I'm not yet sure if that's correct
        delete dynamic_cast<IEtwEnumeratorImpl*>(etwEnumerator);
    }
}
