from enum import Enum, auto


class PlatformType(Enum):
    WINDOWS = auto()
    LINUX = auto()
    MACOS = auto()

    def __str__(self):
        return self.name.lower()

    @staticmethod
    def from_str(label):
        if label in ('windows', 'Windows', 'win'):
            return PlatformType.WINDOWS
        elif label in ('linux', 'Linux'):
            return PlatformType.LINUX
        elif label in ('macos', 'macOS', 'osx'):
            return PlatformType.MACOS
        else:
            raise NotImplementedError
