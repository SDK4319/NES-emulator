#include"MapperInterface.h"
#include"MapperCNROM.h"
#include"MapperNROM.h"
#include"MapperSxROM.h"
#include"MapperUxROM.h"

NameTableMirroring Mapper::getNameTableMirroring() {
	return static_cast<NameTableMirroring>(m_cartridge.getNameTableMirroring());
}

std::unique_ptr<Mapper> Mapper::create(Type mapper_type, Rom& cart,
	std::function<void(void)> mirroring_cb) {
	std::unique_ptr<Mapper> ret(nullptr);
    switch (mapper_type)
    {
    case NROM:
        ret.reset(new MapperNROM(cart));
        break;
    case SxROM:
        ret.reset(new MapperSxROM(cart, mirroring_cb));
        break;
    case UxROM:
        ret.reset(new MapperUxROM(cart));
        break;
    case CNROM:
        ret.reset(new MapperCNROM(cart));
        break;
    default:
        break;
    }
    return ret;
}