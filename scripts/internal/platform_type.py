from enum import Enum, auto


class PlatformType(Enum):
    WINDOWS = auto()
    LINUX = auto()
    MACOS = auto()

    def __str__(self):
        return self.name.lower()

    @staticmethod
    def from_str(label):
        label_lower = label.lower()
        if label_lower in ('windows', 'win'):
            return PlatformType.WINDOWS
        elif label_lower in ('linux', 'ubuntu'):
            return PlatformType.LINUX
        elif label_lower in ('macos', 'osx'):
            return PlatformType.MACOS
        else:
            raise NotImplementedError
