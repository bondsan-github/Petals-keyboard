#pragma once

static enum class service_identifier { window , graphics , write , usages , grid };

struct service 
{
    service_identifier identifier{};
};